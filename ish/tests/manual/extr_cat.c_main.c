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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  perror (char const*) ; 
 int /*<<< orphan*/  putchar (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 

int main(int argc, const char *argv[]) {
    FILE *f = stdin;
    if (argc > 1)
        f = fopen(argv[1], "r");
    if (f == NULL) {
        fprintf(stderr, "cat: ");
        perror(argv[1]);
        return 1;
    }

    int c;
    while ((c = fgetc(f)) != EOF)
        putchar(c);
}