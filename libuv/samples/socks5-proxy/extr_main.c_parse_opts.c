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
struct TYPE_3__ {int /*<<< orphan*/  bind_port; int /*<<< orphan*/  bind_host; } ;
typedef  TYPE_1__ server_config ;

/* Variables and functions */
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int sscanf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage () ; 

__attribute__((used)) static void parse_opts(server_config *cf, int argc, char **argv) {
  int opt;

  while (-1 != (opt = getopt(argc, argv, "b:hp:"))) {
    switch (opt) {
      case 'b':
        cf->bind_host = optarg;
        break;

      case 'p':
        if (1 != sscanf(optarg, "%hu", &cf->bind_port)) {
          pr_err("bad port number: %s", optarg);
          usage();
        }
        break;

      default:
        usage();
    }
  }
}