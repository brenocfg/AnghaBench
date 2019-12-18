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
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
bsdar_usage(void)
{

	(void)fprintf(stderr, "usage:  ar -d [-Tjsvz] archive file ...\n");
	(void)fprintf(stderr, "\tar -m [-Tjsvz] archive file ...\n");
	(void)fprintf(stderr, "\tar -m [-Tabijsvz] position archive file ...\n");
	(void)fprintf(stderr, "\tar -p [-Tv] archive [file ...]\n");
	(void)fprintf(stderr, "\tar -q [-TcDjsUvz] archive file ...\n");
	(void)fprintf(stderr, "\tar -r [-TcDjsUuvz] archive file ...\n");
	(void)fprintf(stderr, "\tar -r [-TabcDijsUuvz] position archive file ...\n");
	(void)fprintf(stderr, "\tar -s [-jz] archive\n");
	(void)fprintf(stderr, "\tar -t [-Tv] archive [file ...]\n");
	(void)fprintf(stderr, "\tar -x [-CTouv] archive [file ...]\n");
	(void)fprintf(stderr, "\tar -V\n");
	exit(EX_USAGE);
}