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
struct config_file {int /*<<< orphan*/  remote_control_enable; } ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 struct config_file* config_create () ; 
 int /*<<< orphan*/  config_delete (struct config_file*) ; 
 int /*<<< orphan*/  config_read (struct config_file*,char const*,int /*<<< orphan*/ *) ; 
 int contact_server (char*,struct config_file*,int) ; 
 int /*<<< orphan*/  fatal_exit (char*) ; 
 int go_cmd (int /*<<< orphan*/ *,int,int,int,char**) ; 
 int /*<<< orphan*/  log_warn (char*) ; 
 int /*<<< orphan*/ * setup_ctx (struct config_file*) ; 
 int /*<<< orphan*/ * setup_ssl (int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  w_config_adjust_directory (struct config_file*) ; 

__attribute__((used)) static int
go(const char* cfgfile, char* svr, int quiet, int argc, char* argv[])
{
	struct config_file* cfg;
	int fd, ret;
	SSL_CTX* ctx;
	SSL* ssl;

	/* read config */
	if(!(cfg = config_create()))
		fatal_exit("out of memory");
	if(!config_read(cfg, cfgfile, NULL))
		fatal_exit("could not read config file");
	if(!cfg->remote_control_enable)
		log_warn("control-enable is 'no' in the config file.");
#ifdef UB_ON_WINDOWS
	w_config_adjust_directory(cfg);
#endif
	ctx = setup_ctx(cfg);

	/* contact server */
	fd = contact_server(svr, cfg, argc>0&&strcmp(argv[0],"status")==0);
	ssl = setup_ssl(ctx, fd);

	/* send command */
	ret = go_cmd(ssl, fd, quiet, argc, argv);

	if(ssl) SSL_free(ssl);
#ifndef USE_WINSOCK
	close(fd);
#else
	closesocket(fd);
#endif
	if(ctx) SSL_CTX_free(ctx);
	config_delete(cfg);
	return ret;
}