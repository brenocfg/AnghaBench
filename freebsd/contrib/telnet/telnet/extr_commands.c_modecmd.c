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
struct modelist {int (* handler ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  arg1; scalar_t__ needconnect; } ;

/* Variables and functions */
 scalar_t__ Ambiguous (void*) ; 
 struct modelist* GETMODECMD (char*) ; 
 int /*<<< orphan*/  connected ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
modecmd(int argc, char *argv[])
{
    struct modelist *mt;

    if (argc != 2) {
	printf("'mode' command requires an argument\n");
	printf("'mode ?' for help.\n");
    } else if ((mt = GETMODECMD(argv[1])) == 0) {
	fprintf(stderr, "Unknown mode '%s' ('mode ?' for help).\n", argv[1]);
    } else if (Ambiguous((void *)mt)) {
	fprintf(stderr, "Ambiguous mode '%s' ('mode ?' for help).\n", argv[1]);
    } else if (mt->needconnect && !connected) {
	printf("?Need to be connected first.\n");
	printf("'mode ?' for help.\n");
    } else if (mt->handler) {
	return (*mt->handler)(mt->arg1);
    }
    return 0;
}