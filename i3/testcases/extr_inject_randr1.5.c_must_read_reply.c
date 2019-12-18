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
struct stat {int st_size; } ;
struct injected_reply {int len; int /*<<< orphan*/  buf; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fread (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  smalloc (int) ; 

__attribute__((used)) static void must_read_reply(const char *filename, struct injected_reply *reply) {
    FILE *f;
    if ((f = fopen(filename, "r")) == NULL) {
        err(EXIT_FAILURE, "fopen(%s)", filename);
    }
    struct stat stbuf;
    if (fstat(fileno(f), &stbuf) != 0) {
        err(EXIT_FAILURE, "fstat(%s)", filename);
    }
    reply->len = stbuf.st_size;
    reply->buf = smalloc(stbuf.st_size);
    int n = fread(reply->buf, 1, stbuf.st_size, f);
    if (n != stbuf.st_size) {
        err(EXIT_FAILURE, "fread(%s)", filename);
    }
    fclose(f);
}