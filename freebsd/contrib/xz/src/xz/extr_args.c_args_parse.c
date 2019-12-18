#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char files_delim; char** arg_names; int arg_count; int /*<<< orphan*/ * files_name; int /*<<< orphan*/ * files_file; } ;
typedef  TYPE_1__ args_info ;

/* Variables and functions */
 scalar_t__ FORMAT_AUTO ; 
 scalar_t__ FORMAT_LZMA ; 
 scalar_t__ FORMAT_RAW ; 
 scalar_t__ FORMAT_XZ ; 
 scalar_t__ MODE_COMPRESS ; 
 scalar_t__ MODE_DECOMPRESS ; 
 scalar_t__ MODE_TEST ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  coder_set_compression_settings () ; 
 int /*<<< orphan*/  message_fatal (int /*<<< orphan*/ ) ; 
 scalar_t__ opt_format ; 
 int opt_keep_original ; 
 scalar_t__ opt_mode ; 
 int opt_stdout ; 
 size_t optind ; 
 int /*<<< orphan*/  parse_environment (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  parse_real (TYPE_1__*,int,char**) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/ * strstr (char const*,char*) ; 

extern void
args_parse(args_info *args, int argc, char **argv)
{
	// Initialize those parts of *args that we need later.
	args->files_name = NULL;
	args->files_file = NULL;
	args->files_delim = '\0';

	// Check how we were called.
	{
		// Remove the leading path name, if any.
		const char *name = strrchr(argv[0], '/');
		if (name == NULL)
			name = argv[0];
		else
			++name;

		// NOTE: It's possible that name[0] is now '\0' if argv[0]
		// is weird, but it doesn't matter here.

		// Look for full command names instead of substrings like
		// "un", "cat", and "lz" to reduce possibility of false
		// positives when the programs have been renamed.
		if (strstr(name, "xzcat") != NULL) {
			opt_mode = MODE_DECOMPRESS;
			opt_stdout = true;
		} else if (strstr(name, "unxz") != NULL) {
			opt_mode = MODE_DECOMPRESS;
		} else if (strstr(name, "lzcat") != NULL) {
			opt_format = FORMAT_LZMA;
			opt_mode = MODE_DECOMPRESS;
			opt_stdout = true;
		} else if (strstr(name, "unlzma") != NULL) {
			opt_format = FORMAT_LZMA;
			opt_mode = MODE_DECOMPRESS;
		} else if (strstr(name, "lzma") != NULL) {
			opt_format = FORMAT_LZMA;
		}
	}

	// First the flags from the environment
	parse_environment(args, argv[0], "XZ_DEFAULTS");
	parse_environment(args, argv[0], "XZ_OPT");

	// Then from the command line
	parse_real(args, argc, argv);

	// If encoder or decoder support was omitted at build time,
	// show an error now so that the rest of the code can rely on
	// that whatever is in opt_mode is also supported.
#ifndef HAVE_ENCODERS
	if (opt_mode == MODE_COMPRESS)
		message_fatal(_("Compression support was disabled "
				"at build time"));
#endif
#ifndef HAVE_DECODERS
	// Even MODE_LIST cannot work without decoder support so MODE_COMPRESS
	// is the only valid choice.
	if (opt_mode != MODE_COMPRESS)
		message_fatal(_("Decompression support was disabled "
				"at build time"));
#endif

	// Never remove the source file when the destination is not on disk.
	// In test mode the data is written nowhere, but setting opt_stdout
	// will make the rest of the code behave well.
	if (opt_stdout || opt_mode == MODE_TEST) {
		opt_keep_original = true;
		opt_stdout = true;
	}

	// When compressing, if no --format flag was used, or it
	// was --format=auto, we compress to the .xz format.
	if (opt_mode == MODE_COMPRESS && opt_format == FORMAT_AUTO)
		opt_format = FORMAT_XZ;

	// Compression settings need to be validated (options themselves and
	// their memory usage) when compressing to any file format. It has to
	// be done also when uncompressing raw data, since for raw decoding
	// the options given on the command line are used to know what kind
	// of raw data we are supposed to decode.
	if (opt_mode == MODE_COMPRESS || opt_format == FORMAT_RAW)
		coder_set_compression_settings();

	// If no filenames are given, use stdin.
	if (argv[optind] == NULL && args->files_name == NULL) {
		// We don't modify or free() the "-" constant. The caller
		// modifies this so don't make the struct itself const.
		static char *names_stdin[2] = { (char *)"-", NULL };
		args->arg_names = names_stdin;
		args->arg_count = 1;
	} else {
		// We got at least one filename from the command line, or
		// --files or --files0 was specified.
		args->arg_names = argv + optind;
		args->arg_count = argc - optind;
	}

	return;
}