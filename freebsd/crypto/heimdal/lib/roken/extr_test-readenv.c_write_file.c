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
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ fwrite (char const*,int,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  unlink (char const*) ; 

__attribute__((used)) static void
write_file(const char *fn, const char *s)
{
    FILE *f;
    f = fopen(fn, "w");
    if(f == NULL) {
	unlink(fn);
	err(1, "fopen");
    }
    if(fwrite(s, 1, strlen(s), f) != strlen(s))
	err(1, "short write");
    if(fclose(f) != 0) {
	unlink(fn);
	err(1, "fclose");
    }
}