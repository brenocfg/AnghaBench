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
struct TYPE_5__ {int /*<<< orphan*/  idle_timeout; int /*<<< orphan*/  bind_port; int /*<<< orphan*/  bind_host; } ;
typedef  TYPE_1__ server_config ;
typedef  int /*<<< orphan*/  config ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_BIND_HOST ; 
 int /*<<< orphan*/  DEFAULT_BIND_PORT ; 
 int /*<<< orphan*/  DEFAULT_IDLE_TIMEOUT ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_opts (TYPE_1__*,int,char**) ; 
 char* progname ; 
 int server_run (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_default_loop () ; 

int main(int argc, char **argv) {
  server_config config;
  int err;

  progname = argv[0];
  memset(&config, 0, sizeof(config));
  config.bind_host = DEFAULT_BIND_HOST;
  config.bind_port = DEFAULT_BIND_PORT;
  config.idle_timeout = DEFAULT_IDLE_TIMEOUT;
  parse_opts(&config, argc, argv);

  err = server_run(&config, uv_default_loop());
  if (err) {
    exit(1);
  }

  return 0;
}