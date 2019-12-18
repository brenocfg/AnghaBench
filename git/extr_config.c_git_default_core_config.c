#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int hexsz; } ;

/* Variables and functions */
 int AUTO_CRLF_INPUT ; 
 int /*<<< orphan*/  CONV_EOL_RNDTRP_DIE ; 
 int /*<<< orphan*/  CONV_EOL_RNDTRP_WARN ; 
 int /*<<< orphan*/  EOL_CRLF ; 
 int /*<<< orphan*/  EOL_LF ; 
 int /*<<< orphan*/  EOL_NATIVE ; 
 int /*<<< orphan*/  EOL_UNSET ; 
 int /*<<< orphan*/  LOG_REFS_ALWAYS ; 
 int /*<<< orphan*/  LOG_REFS_NONE ; 
 int /*<<< orphan*/  LOG_REFS_NORMAL ; 
 int /*<<< orphan*/  OBJECT_CREATION_USES_HARDLINKS ; 
 int /*<<< orphan*/  OBJECT_CREATION_USES_RENAMES ; 
 int Z_BEST_COMPRESSION ; 
 int Z_DEFAULT_COMPRESSION ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  askpass_program ; 
 int assume_unchanged ; 
 int auto_comment_line_char ; 
 int auto_crlf ; 
 void* big_file_threshold ; 
 void* check_roundtrip_encoding ; 
 int check_stat ; 
 char comment_line_char ; 
 int config_error_nonbool (char const*) ; 
 int core_apply_sparse_checkout ; 
 int core_compression_level ; 
 int core_compression_seen ; 
 int /*<<< orphan*/  core_eol ; 
 int core_preload_index ; 
 int default_abbrev ; 
 void* delta_base_cache_limit ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  editor_program ; 
 int error (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  excludes_file ; 
 int fsync_object_files ; 
 int getpagesize () ; 
 int /*<<< orphan*/  git_attributes_file ; 
 int git_config_bool (char const*,char const*) ; 
 int git_config_int (char const*,char const*) ; 
 int git_config_pathname (int /*<<< orphan*/ *,char const*,char const*) ; 
 int git_config_string (int /*<<< orphan*/ *,char const*,char const*) ; 
 void* git_config_ulong (char const*,char const*) ; 
 int /*<<< orphan*/  git_hooks_path ; 
 int /*<<< orphan*/  global_conv_flags_eol ; 
 int has_symlinks ; 
 int ignore_case ; 
 int is_bare_repository_cfg ; 
 int /*<<< orphan*/  log_all_ref_updates ; 
 int minimum_abbrev ; 
 void* notes_ref_name ; 
 int /*<<< orphan*/  object_creation_mode ; 
 int pack_compression_level ; 
 int /*<<< orphan*/  pack_compression_seen ; 
 void* packed_git_limit ; 
 int packed_git_window_size ; 
 int /*<<< orphan*/  parse_whitespace_rule (char const*) ; 
 int platform_core_config (char const*,char const*,void*) ; 
 int precomposed_unicode ; 
 int prefer_symlink_refs ; 
 int protect_hfs ; 
 int protect_ntfs ; 
 int quote_path_fully ; 
 int read_replace_refs ; 
 int set_disambiguate_hint_config (char const*,char const*) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 TYPE_1__* the_hash_algo ; 
 int trust_ctime ; 
 int trust_executable_bit ; 
 int warn_ambiguous_refs ; 
 int /*<<< orphan*/  whitespace_rule_cfg ; 
 void* xstrdup (char const*) ; 
 int zlib_compression_level ; 
 int zlib_compression_seen ; 

__attribute__((used)) static int git_default_core_config(const char *var, const char *value, void *cb)
{
	/* This needs a better name */
	if (!strcmp(var, "core.filemode")) {
		trust_executable_bit = git_config_bool(var, value);
		return 0;
	}
	if (!strcmp(var, "core.trustctime")) {
		trust_ctime = git_config_bool(var, value);
		return 0;
	}
	if (!strcmp(var, "core.checkstat")) {
		if (!strcasecmp(value, "default"))
			check_stat = 1;
		else if (!strcasecmp(value, "minimal"))
			check_stat = 0;
	}

	if (!strcmp(var, "core.quotepath")) {
		quote_path_fully = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "core.symlinks")) {
		has_symlinks = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "core.ignorecase")) {
		ignore_case = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "core.attributesfile"))
		return git_config_pathname(&git_attributes_file, var, value);

	if (!strcmp(var, "core.hookspath"))
		return git_config_pathname(&git_hooks_path, var, value);

	if (!strcmp(var, "core.bare")) {
		is_bare_repository_cfg = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "core.ignorestat")) {
		assume_unchanged = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "core.prefersymlinkrefs")) {
		prefer_symlink_refs = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "core.logallrefupdates")) {
		if (value && !strcasecmp(value, "always"))
			log_all_ref_updates = LOG_REFS_ALWAYS;
		else if (git_config_bool(var, value))
			log_all_ref_updates = LOG_REFS_NORMAL;
		else
			log_all_ref_updates = LOG_REFS_NONE;
		return 0;
	}

	if (!strcmp(var, "core.warnambiguousrefs")) {
		warn_ambiguous_refs = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "core.abbrev")) {
		if (!value)
			return config_error_nonbool(var);
		if (!strcasecmp(value, "auto"))
			default_abbrev = -1;
		else {
			int abbrev = git_config_int(var, value);
			if (abbrev < minimum_abbrev || abbrev > the_hash_algo->hexsz)
				return error(_("abbrev length out of range: %d"), abbrev);
			default_abbrev = abbrev;
		}
		return 0;
	}

	if (!strcmp(var, "core.disambiguate"))
		return set_disambiguate_hint_config(var, value);

	if (!strcmp(var, "core.loosecompression")) {
		int level = git_config_int(var, value);
		if (level == -1)
			level = Z_DEFAULT_COMPRESSION;
		else if (level < 0 || level > Z_BEST_COMPRESSION)
			die(_("bad zlib compression level %d"), level);
		zlib_compression_level = level;
		zlib_compression_seen = 1;
		return 0;
	}

	if (!strcmp(var, "core.compression")) {
		int level = git_config_int(var, value);
		if (level == -1)
			level = Z_DEFAULT_COMPRESSION;
		else if (level < 0 || level > Z_BEST_COMPRESSION)
			die(_("bad zlib compression level %d"), level);
		core_compression_level = level;
		core_compression_seen = 1;
		if (!zlib_compression_seen)
			zlib_compression_level = level;
		if (!pack_compression_seen)
			pack_compression_level = level;
		return 0;
	}

	if (!strcmp(var, "core.packedgitwindowsize")) {
		int pgsz_x2 = getpagesize() * 2;
		packed_git_window_size = git_config_ulong(var, value);

		/* This value must be multiple of (pagesize * 2) */
		packed_git_window_size /= pgsz_x2;
		if (packed_git_window_size < 1)
			packed_git_window_size = 1;
		packed_git_window_size *= pgsz_x2;
		return 0;
	}

	if (!strcmp(var, "core.bigfilethreshold")) {
		big_file_threshold = git_config_ulong(var, value);
		return 0;
	}

	if (!strcmp(var, "core.packedgitlimit")) {
		packed_git_limit = git_config_ulong(var, value);
		return 0;
	}

	if (!strcmp(var, "core.deltabasecachelimit")) {
		delta_base_cache_limit = git_config_ulong(var, value);
		return 0;
	}

	if (!strcmp(var, "core.autocrlf")) {
		if (value && !strcasecmp(value, "input")) {
			auto_crlf = AUTO_CRLF_INPUT;
			return 0;
		}
		auto_crlf = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "core.safecrlf")) {
		int eol_rndtrp_die;
		if (value && !strcasecmp(value, "warn")) {
			global_conv_flags_eol = CONV_EOL_RNDTRP_WARN;
			return 0;
		}
		eol_rndtrp_die = git_config_bool(var, value);
		global_conv_flags_eol = eol_rndtrp_die ?
			CONV_EOL_RNDTRP_DIE : 0;
		return 0;
	}

	if (!strcmp(var, "core.eol")) {
		if (value && !strcasecmp(value, "lf"))
			core_eol = EOL_LF;
		else if (value && !strcasecmp(value, "crlf"))
			core_eol = EOL_CRLF;
		else if (value && !strcasecmp(value, "native"))
			core_eol = EOL_NATIVE;
		else
			core_eol = EOL_UNSET;
		return 0;
	}

	if (!strcmp(var, "core.checkroundtripencoding")) {
		check_roundtrip_encoding = xstrdup(value);
		return 0;
	}

	if (!strcmp(var, "core.notesref")) {
		notes_ref_name = xstrdup(value);
		return 0;
	}

	if (!strcmp(var, "core.editor"))
		return git_config_string(&editor_program, var, value);

	if (!strcmp(var, "core.commentchar")) {
		if (!value)
			return config_error_nonbool(var);
		else if (!strcasecmp(value, "auto"))
			auto_comment_line_char = 1;
		else if (value[0] && !value[1]) {
			comment_line_char = value[0];
			auto_comment_line_char = 0;
		} else
			return error(_("core.commentChar should only be one character"));
		return 0;
	}

	if (!strcmp(var, "core.askpass"))
		return git_config_string(&askpass_program, var, value);

	if (!strcmp(var, "core.excludesfile"))
		return git_config_pathname(&excludes_file, var, value);

	if (!strcmp(var, "core.whitespace")) {
		if (!value)
			return config_error_nonbool(var);
		whitespace_rule_cfg = parse_whitespace_rule(value);
		return 0;
	}

	if (!strcmp(var, "core.fsyncobjectfiles")) {
		fsync_object_files = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "core.preloadindex")) {
		core_preload_index = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "core.createobject")) {
		if (!strcmp(value, "rename"))
			object_creation_mode = OBJECT_CREATION_USES_RENAMES;
		else if (!strcmp(value, "link"))
			object_creation_mode = OBJECT_CREATION_USES_HARDLINKS;
		else
			die(_("invalid mode for object creation: %s"), value);
		return 0;
	}

	if (!strcmp(var, "core.sparsecheckout")) {
		core_apply_sparse_checkout = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "core.precomposeunicode")) {
		precomposed_unicode = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "core.protecthfs")) {
		protect_hfs = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "core.protectntfs")) {
		protect_ntfs = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "core.usereplacerefs")) {
		read_replace_refs = git_config_bool(var, value);
		return 0;
	}

	/* Add other config variables here and to Documentation/config.txt. */
	return platform_core_config(var, value, cb);
}