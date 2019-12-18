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
struct finfo {char* name; int /*<<< orphan*/  size; } ;
struct buf {int /*<<< orphan*/  size; int /*<<< orphan*/  start; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fread (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fwread(struct finfo *finfo, struct buf *buf)
{
    FILE *f;
    
    f = fopen(finfo->name, "r");
    if (!f) {
	fprintf(stderr, "could not open \"%s\" for reading\n", finfo->name);
	usage(EXIT_FAILURE);
    }

    buf->size = fread(buf->start, 1, finfo->size, f);
    if (buf->size != finfo->size) {
	fprintf(stderr, "unable to read from file \"%s\"\n", finfo->name);
	usage(EXIT_FAILURE);
    }

    fclose(f);

    return EXIT_SUCCESS;
}