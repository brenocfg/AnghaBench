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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ * const) ; 
 scalar_t__ ferror (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ fwrite (int /*<<< orphan*/  const*,int,size_t,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void write_file(const char *path, const u8 *ptr, size_t size)
{
    FILE* const f = fopen(path, "wb");
    if (!f) {
        fprintf(stderr, "failed to open file %s \n", path);
        exit(1);
    }

    size_t written = 0;
    while (written < size) {
        written += fwrite(ptr+written, 1, size, f);
        if (ferror(f)) {
            fprintf(stderr, "error while writing file %s\n", path);
            exit(1);
    }   }

    fclose(f);
}