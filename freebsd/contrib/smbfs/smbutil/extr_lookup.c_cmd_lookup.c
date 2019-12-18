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
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sin_addr; } ;
struct nb_ctx {TYPE_1__ nb_lastns; } ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 char* inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lookup_usage () ; 
 int nb_ctx_create (struct nb_ctx**) ; 
 scalar_t__ nb_ctx_readrcsection (int /*<<< orphan*/ ,struct nb_ctx*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ nb_ctx_resolve (struct nb_ctx*) ; 
 int /*<<< orphan*/  nb_ctx_setns (struct nb_ctx*,int /*<<< orphan*/ ) ; 
 int nbns_resolvename (char*,struct nb_ctx*,struct sockaddr**) ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  rc_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_error (char*,int,...) ; 
 scalar_t__ smb_open_rcfile () ; 
 int /*<<< orphan*/  smb_rc ; 

int
cmd_lookup(int argc, char *argv[])
{
	struct nb_ctx *ctx;
	struct sockaddr *sap;
	char *hostname;
	int error, opt;

	if (argc < 2)
		lookup_usage();
	error = nb_ctx_create(&ctx);
	if (error) {
		smb_error("unable to create nbcontext", error);
		exit(1);
	}
	if (smb_open_rcfile() == 0) {
		if (nb_ctx_readrcsection(smb_rc, ctx, "default", 0) != 0)
			exit(1);
		rc_close(smb_rc);
	}
	while ((opt = getopt(argc, argv, "w:")) != EOF) {
		switch(opt){
		    case 'w':
			nb_ctx_setns(ctx, optarg);
			break;
		    default:
			lookup_usage();
			/*NOTREACHED*/
		}
	}
	if (optind >= argc)
		lookup_usage();
	if (nb_ctx_resolve(ctx) != 0)
		exit(1);
	hostname = argv[argc - 1];
/*	printf("Looking for %s...\n", hostname);*/
	error = nbns_resolvename(hostname, ctx, &sap);
	if (error) {
		smb_error("unable to resolve %s", error, hostname);
		exit(1);
	}
	printf("Got response from %s\n", inet_ntoa(ctx->nb_lastns.sin_addr));
	printf("IP address of %s: %s\n", hostname, inet_ntoa(((struct sockaddr_in*)sap)->sin_addr));
	return 0;
}