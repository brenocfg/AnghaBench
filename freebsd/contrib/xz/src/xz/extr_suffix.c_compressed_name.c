#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int FORMAT_AUTO ; 
 int FORMAT_RAW ; 
 int FORMAT_XZ ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _use_lfn (char const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 char const* custom_suffix ; 
 scalar_t__ has_dir_sep (char const*) ; 
 scalar_t__ has_sfn_suffix (char const*,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  message_error (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  msg_suffix (char const*,char const*) ; 
 int opt_format ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 int strlen (char const*) ; 
 char* strrchr (char const*,char) ; 
 scalar_t__ test_suffix (char const*,char const*,size_t) ; 
 char* xmalloc (size_t) ; 

__attribute__((used)) static char *
compressed_name(const char *src_name, size_t src_len)
{
	// The order of these must match the order in args.h.
	static const char *const all_suffixes[][4] = {
		{
			".xz",
			".txz",
			NULL
		}, {
			".lzma",
#ifdef __DJGPP__
			".lzm",
#endif
			".tlz",
			NULL
/*
		}, {
			".gz",
			".tgz",
			NULL
*/
		}, {
			// --format=raw requires specifying the suffix
			// manually or using stdout.
			NULL
		}
	};

	// args.c ensures this.
	assert(opt_format != FORMAT_AUTO);

	const size_t format = opt_format - 1;
	const char *const *suffixes = all_suffixes[format];

	// Look for known filename suffixes and refuse to compress them.
	for (size_t i = 0; suffixes[i] != NULL; ++i) {
		if (test_suffix(suffixes[i], src_name, src_len) != 0) {
			msg_suffix(src_name, suffixes[i]);
			return NULL;
		}
	}

#ifdef __DJGPP__
	// Recognize also the special suffix that is used when long
	// filename (LFN) support isn't available. This suffix is
	// recognized on LFN systems too.
	if (opt_format == FORMAT_XZ && has_sfn_suffix(src_name, src_len)) {
		msg_suffix(src_name, "-");
		return NULL;
	}
#endif

	if (custom_suffix != NULL) {
		if (test_suffix(custom_suffix, src_name, src_len) != 0) {
			msg_suffix(src_name, custom_suffix);
			return NULL;
		}
	}

	// TODO: Hmm, maybe it would be better to validate this in args.c,
	// since the suffix handling when decoding is weird now.
	if (opt_format == FORMAT_RAW && custom_suffix == NULL) {
		message_error(_("%s: With --format=raw, "
				"--suffix=.SUF is required unless "
				"writing to stdout"), src_name);
		return NULL;
	}

	const char *suffix = custom_suffix != NULL
			? custom_suffix : suffixes[0];
	size_t suffix_len = strlen(suffix);

#ifdef __DJGPP__
	if (!_use_lfn(src_name)) {
		// Long filename (LFN) support isn't available and we are
		// limited to 8.3 short filenames (SFN).
		//
		// Look for suffix separator from the filename, and make sure
		// that it is in the filename, not in a directory name.
		const char *sufsep = strrchr(src_name, '.');
		if (sufsep == NULL || sufsep[1] == '\0'
				|| has_dir_sep(sufsep)) {
			// src_name has no filename extension.
			//
			// Examples:
			// xz foo         -> foo.xz
			// xz -F lzma foo -> foo.lzm
			// xz -S x foo    -> foox
			// xz -S x foo.   -> foo.x
			// xz -S x.y foo  -> foox.y
			// xz -S .x foo   -> foo.x
			// xz -S .x foo.  -> foo.x
			//
			// Avoid double dots:
			if (sufsep != NULL && sufsep[1] == '\0'
					&& suffix[0] == '.')
				--src_len;

		} else if (custom_suffix == NULL
				&& strcasecmp(sufsep, ".tar") == 0) {
			// ".tar" is handled specially.
			//
			// Examples:
			// xz foo.tar          -> foo.txz
			// xz -F lzma foo.tar  -> foo.tlz
			static const char *const tar_suffixes[] = {
				".txz",
				".tlz",
				// ".tgz",
			};
			suffix = tar_suffixes[format];
			suffix_len = 4;
			src_len -= 4;

		} else {
			if (custom_suffix == NULL && opt_format == FORMAT_XZ) {
				// Instead of the .xz suffix, use a single
				// character at the end of the filename
				// extension. This is to minimize name
				// conflicts when compressing multiple files
				// with the same basename. E.g. foo.txt and
				// foo.exe become foo.tx- and foo.ex-. Dash
				// is rare as the last character of the
				// filename extension, so it seems to be
				// quite safe choice and it stands out better
				// in directory listings than e.g. x. For
				// comparison, gzip uses z.
				suffix = "-";
				suffix_len = 1;
			}

			if (suffix[0] == '.') {
				// The first character of the suffix is a dot.
				// Throw away the original filename extension
				// and replace it with the new suffix.
				//
				// Examples:
				// xz -F lzma foo.txt  -> foo.lzm
				// xz -S .x  foo.txt   -> foo.x
				src_len = sufsep - src_name;

			} else {
				// The first character of the suffix is not
				// a dot. Preserve the first 0-2 characters
				// of the original filename extension.
				//
				// Examples:
				// xz foo.txt         -> foo.tx-
				// xz -S x  foo.c     -> foo.cx
				// xz -S ab foo.c     -> foo.cab
				// xz -S ab foo.txt   -> foo.tab
				// xz -S abc foo.txt  -> foo.abc
				//
				// Truncate the suffix to three chars:
				if (suffix_len > 3)
					suffix_len = 3;

				// If needed, overwrite 1-3 characters.
				if (strlen(sufsep) > 4 - suffix_len)
					src_len = sufsep - src_name
							+ 4 - suffix_len;
			}
		}
	}
#endif

	char *dest_name = xmalloc(src_len + suffix_len + 1);

	memcpy(dest_name, src_name, src_len);
	memcpy(dest_name + src_len, suffix, suffix_len);
	dest_name[src_len + suffix_len] = '\0';

	return dest_name;
}