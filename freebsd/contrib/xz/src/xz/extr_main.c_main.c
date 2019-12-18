#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum exit_status_type { ____Placeholder_exit_status_type } exit_status_type ;
struct TYPE_4__ {int arg_count; char** arg_names; int /*<<< orphan*/  files_file; int /*<<< orphan*/ * files_name; } ;
typedef  TYPE_1__ args_info ;

/* Variables and functions */
 int E_ERROR ; 
 int E_SUCCESS ; 
 int E_WARNING ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitializeCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOCALEDIR ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ MODE_COMPRESS ; 
 scalar_t__ MODE_LIST ; 
 int /*<<< orphan*/  PACKAGE ; 
 scalar_t__ V_SILENT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  args_free () ; 
 int /*<<< orphan*/  args_parse (TYPE_1__*,int,char**) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  coder_free () ; 
 void coder_run (char const*) ; 
 int exit_status ; 
 int /*<<< orphan*/  exit_status_cs ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hardware_init () ; 
 int /*<<< orphan*/  io_allow_sandbox () ; 
 int /*<<< orphan*/  io_init () ; 
 scalar_t__ is_tty_stdin () ; 
 scalar_t__ is_tty_stdout () ; 
 void list_file (char const*) ; 
 int /*<<< orphan*/  list_totals () ; 
 int /*<<< orphan*/  message_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  message_fatal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  message_init () ; 
 int /*<<< orphan*/  message_set_files (int) ; 
 int /*<<< orphan*/  message_try_help () ; 
 scalar_t__ message_verbosity_get () ; 
 scalar_t__ no_warn ; 
 scalar_t__ opt_mode ; 
 scalar_t__ opt_robot ; 
 scalar_t__ opt_stdout ; 
 char* read_name (TYPE_1__*) ; 
 int /*<<< orphan*/  signals_exit () ; 
 int /*<<< orphan*/  signals_init () ; 
 int /*<<< orphan*/ * stdin_filename ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  tuklib_exit (int,int,int) ; 
 int /*<<< orphan*/  tuklib_gettext_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuklib_progname_init (char**) ; 
 int /*<<< orphan*/  user_abort ; 

int
main(int argc, char **argv)
{
#if defined(_WIN32) && !defined(__CYGWIN__)
	InitializeCriticalSection(&exit_status_cs);
#endif

	// Set up the progname variable.
	tuklib_progname_init(argv);

	// Initialize the file I/O. This makes sure that
	// stdin, stdout, and stderr are something valid.
	io_init();

	// Set up the locale and message translations.
	tuklib_gettext_init(PACKAGE, LOCALEDIR);

	// Initialize handling of error/warning/other messages.
	message_init();

	// Set hardware-dependent default values. These can be overriden
	// on the command line, thus this must be done before args_parse().
	hardware_init();

	// Parse the command line arguments and get an array of filenames.
	// This doesn't return if something is wrong with the command line
	// arguments. If there are no arguments, one filename ("-") is still
	// returned to indicate stdin.
	args_info args;
	args_parse(&args, argc, argv);

	if (opt_mode != MODE_LIST && opt_robot)
		message_fatal(_("Compression and decompression with --robot "
			"are not supported yet."));

	// Tell the message handling code how many input files there are if
	// we know it. This way the progress indicator can show it.
	if (args.files_name != NULL)
		message_set_files(0);
	else
		message_set_files(args.arg_count);

	// Refuse to write compressed data to standard output if it is
	// a terminal.
	if (opt_mode == MODE_COMPRESS) {
		if (opt_stdout || (args.arg_count == 1
				&& strcmp(args.arg_names[0], "-") == 0)) {
			if (is_tty_stdout()) {
				message_try_help();
				tuklib_exit(E_ERROR, E_ERROR, false);
			}
		}
	}

	// Set up the signal handlers. We don't need these before we
	// start the actual action and not in --list mode, so this is
	// done after parsing the command line arguments.
	//
	// It's good to keep signal handlers in normal compression and
	// decompression modes even when only writing to stdout, because
	// we might need to restore O_APPEND flag on stdout before exiting.
	// In --test mode, signal handlers aren't really needed, but let's
	// keep them there for consistency with normal decompression.
	if (opt_mode != MODE_LIST)
		signals_init();

#ifdef ENABLE_SANDBOX
	// Set a flag that sandboxing is allowed if all these are true:
	//   - --files or --files0 wasn't used.
	//   - There is exactly one input file or we are reading from stdin.
	//   - We won't create any files: output goes to stdout or --test
	//     or --list was used. Note that --test implies opt_stdout = true
	//     but --list doesn't.
	//
	// This is obviously not ideal but it was easy to implement and
	// it covers the most common use cases.
	//
	// TODO: Make sandboxing work for other situations too.
	if (args.files_name == NULL && args.arg_count == 1
			&& (opt_stdout || strcmp("-", args.arg_names[0]) == 0
				|| opt_mode == MODE_LIST))
		io_allow_sandbox();
#endif

	// coder_run() handles compression, decompression, and testing.
	// list_file() is for --list.
	void (*run)(const char *filename) = &coder_run;
#ifdef HAVE_DECODERS
	if (opt_mode == MODE_LIST)
		run = &list_file;
#endif

	// Process the files given on the command line. Note that if no names
	// were given, args_parse() gave us a fake "-" filename.
	for (unsigned i = 0; i < args.arg_count && !user_abort; ++i) {
		if (strcmp("-", args.arg_names[i]) == 0) {
			// Processing from stdin to stdout. Check that we
			// aren't writing compressed data to a terminal or
			// reading it from a terminal.
			if (opt_mode == MODE_COMPRESS) {
				if (is_tty_stdout())
					continue;
			} else if (is_tty_stdin()) {
				continue;
			}

			// It doesn't make sense to compress data from stdin
			// if we are supposed to read filenames from stdin
			// too (enabled with --files or --files0).
			if (args.files_name == stdin_filename) {
				message_error(_("Cannot read data from "
						"standard input when "
						"reading filenames "
						"from standard input"));
				continue;
			}

			// Replace the "-" with a special pointer, which is
			// recognized by coder_run() and other things.
			// This way error messages get a proper filename
			// string and the code still knows that it is
			// handling the special case of stdin.
			args.arg_names[i] = (char *)stdin_filename;
		}

		// Do the actual compression or decompression.
		run(args.arg_names[i]);
	}

	// If --files or --files0 was used, process the filenames from the
	// given file or stdin. Note that here we don't consider "-" to
	// indicate stdin like we do with the command line arguments.
	if (args.files_name != NULL) {
		// read_name() checks for user_abort so we don't need to
		// check it as loop termination condition.
		while (true) {
			const char *name = read_name(&args);
			if (name == NULL)
				break;

			// read_name() doesn't return empty names.
			assert(name[0] != '\0');
			run(name);
		}

		if (args.files_name != stdin_filename)
			(void)fclose(args.files_file);
	}

#ifdef HAVE_DECODERS
	// All files have now been handled. If in --list mode, display
	// the totals before exiting. We don't have signal handlers
	// enabled in --list mode, so we don't need to check user_abort.
	if (opt_mode == MODE_LIST) {
		assert(!user_abort);
		list_totals();
	}
#endif

#ifndef NDEBUG
	coder_free();
	args_free();
#endif

	// If we have got a signal, raise it to kill the program instead
	// of calling tuklib_exit().
	signals_exit();

	// Make a local copy of exit_status to keep the Windows code
	// thread safe. At this point it is fine if we miss the user
	// pressing C-c and don't set the exit_status to E_ERROR on
	// Windows.
#if defined(_WIN32) && !defined(__CYGWIN__)
	EnterCriticalSection(&exit_status_cs);
#endif

	enum exit_status_type es = exit_status;

#if defined(_WIN32) && !defined(__CYGWIN__)
	LeaveCriticalSection(&exit_status_cs);
#endif

	// Suppress the exit status indicating a warning if --no-warn
	// was specified.
	if (es == E_WARNING && no_warn)
		es = E_SUCCESS;

	tuklib_exit(es, E_ERROR, message_verbosity_get() != V_SILENT);
}