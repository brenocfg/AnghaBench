#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ev_timer {int /*<<< orphan*/ * data; } ;
struct Startup_Sequence {int /*<<< orphan*/ * context; void* workspace; void* id; } ;
struct TYPE_3__ {char const* name; } ;
typedef  int /*<<< orphan*/  SnLauncherContext ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (char*,char const*) ; 
 int /*<<< orphan*/  RLIMIT_CORE ; 
 int SD_LISTEN_FDS_START ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct Startup_Sequence*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XCURSOR_CURSOR_WATCH ; 
 int /*<<< orphan*/  _PATH_BSHELL ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 TYPE_1__* con_get_workspace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn_screen ; 
 int /*<<< orphan*/  current_socketpath ; 
 int /*<<< orphan*/  ev_timer_init (struct ev_timer*,int /*<<< orphan*/ ,double,int) ; 
 int /*<<< orphan*/  ev_timer_start (int /*<<< orphan*/ ,struct ev_timer*) ; 
 int /*<<< orphan*/  execl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  focused ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  last_timestamp ; 
 int listen_fds ; 
 int /*<<< orphan*/  main_loop ; 
 int /*<<< orphan*/  original_rlimit_core ; 
 void* scalloc (int,int) ; 
 int /*<<< orphan*/  sequences ; 
 int /*<<< orphan*/  setenv (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setrlimit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setsid () ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char const* sn_launcher_context_get_startup_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sn_launcher_context_initiate (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sn_launcher_context_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sn_launcher_context_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sn_launcher_context_set_description (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sn_launcher_context_set_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sn_launcher_context_setup_child_process (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sndisplay ; 
 void* sstrdup (char const*) ; 
 int /*<<< orphan*/  startup_sequences ; 
 int /*<<< orphan*/  startup_timeout ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  unsetenv (char*) ; 
 int /*<<< orphan*/  wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_set_root_cursor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcursor_set_root_cursor (int /*<<< orphan*/ ) ; 
 scalar_t__ xcursor_supported ; 

void start_application(const char *command, bool no_startup_id) {
    SnLauncherContext *context = NULL;

    if (!no_startup_id) {
        /* Create a startup notification context to monitor the progress of this
         * startup. */
        context = sn_launcher_context_new(sndisplay, conn_screen);
        sn_launcher_context_set_name(context, "i3");
        sn_launcher_context_set_description(context, "exec command in i3");
        /* Chop off everything starting from the first space (if there are any
         * spaces in the command), since we don’t want the parameters. */
        char *first_word = sstrdup(command);
        char *space = strchr(first_word, ' ');
        if (space)
            *space = '\0';
        sn_launcher_context_initiate(context, "i3", first_word, last_timestamp);
        free(first_word);

        /* Trigger a timeout after 60 seconds */
        struct ev_timer *timeout = scalloc(1, sizeof(struct ev_timer));
        ev_timer_init(timeout, startup_timeout, 60.0, 0.);
        timeout->data = context;
        ev_timer_start(main_loop, timeout);

        LOG("startup id = %s\n", sn_launcher_context_get_startup_id(context));

        /* Save the ID and current workspace in our internal list of startup
         * sequences */
        Con *ws = con_get_workspace(focused);
        struct Startup_Sequence *sequence = scalloc(1, sizeof(struct Startup_Sequence));
        sequence->id = sstrdup(sn_launcher_context_get_startup_id(context));
        sequence->workspace = sstrdup(ws->name);
        sequence->context = context;
        TAILQ_INSERT_TAIL(&startup_sequences, sequence, sequences);

        /* Increase the refcount once (it starts with 1, so it will be 2 now) for
         * the timeout. Even if the sequence gets completed, the timeout still
         * needs the context (but will unref it then) */
        sn_launcher_context_ref(context);
    }

    LOG("executing: %s\n", command);
    if (fork() == 0) {
        /* Child process */
        setsid();
        setrlimit(RLIMIT_CORE, &original_rlimit_core);
        /* Close all socket activation file descriptors explicitly, we disabled
         * FD_CLOEXEC to keep them open when restarting i3. */
        for (int fd = SD_LISTEN_FDS_START;
             fd < (SD_LISTEN_FDS_START + listen_fds);
             fd++) {
            close(fd);
        }
        unsetenv("LISTEN_PID");
        unsetenv("LISTEN_FDS");
        signal(SIGPIPE, SIG_DFL);
        if (fork() == 0) {
            /* Setup the environment variable(s) */
            if (!no_startup_id)
                sn_launcher_context_setup_child_process(context);
            setenv("I3SOCK", current_socketpath, 1);

            execl(_PATH_BSHELL, _PATH_BSHELL, "-c", command, NULL);
            /* not reached */
        }
        _exit(0);
    }
    wait(0);

    if (!no_startup_id) {
        /* Change the pointer of the root window to indicate progress */
        if (xcursor_supported)
            xcursor_set_root_cursor(XCURSOR_CURSOR_WATCH);
        else
            xcb_set_root_cursor(XCURSOR_CURSOR_WATCH);
    }
}