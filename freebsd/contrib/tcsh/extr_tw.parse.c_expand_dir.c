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
struct Strbuf {int len; char const* s; } ;
typedef  int /*<<< orphan*/  DIR ;
typedef  char const Char ;
typedef  scalar_t__ COMMAND ;

/* Variables and functions */
 int /*<<< orphan*/  CGETS (int,int,char*) ; 
 scalar_t__ ENOENT ; 
 scalar_t__ ENOTDIR ; 
 int NeedsRedraw ; 
 scalar_t__ SPELL ; 
 char const* STRdot ; 
 scalar_t__ SYM_EXPAND ; 
 scalar_t__ SYM_IGNORE ; 
 scalar_t__ SearchNoDirErr ; 
 int /*<<< orphan*/  Strbuf_append (struct Strbuf*,char const*) ; 
 int /*<<< orphan*/  Strbuf_append1 (struct Strbuf*,char) ; 
 int /*<<< orphan*/  Strbuf_terminate (struct Strbuf*) ; 
 int /*<<< orphan*/  cleanup_push (char const*,int /*<<< orphan*/  (*) (char const*)) ; 
 int /*<<< orphan*/  cleanup_until (char const*) ; 
 char* dnormalize (char const*,int) ; 
 char* dollar (char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  short2str (char const*) ; 
 scalar_t__ symlinks ; 
 scalar_t__ tilde (struct Strbuf*,char const*) ; 
 int /*<<< orphan*/  xfree (char const*) ; 
 int /*<<< orphan*/  xprintf (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
expand_dir(const Char *dir, struct Strbuf *edir, DIR **dfd, COMMAND cmd)
{
    Char   *nd = NULL;
    Char *tdir;

    tdir = dollar(dir);
    cleanup_push(tdir, xfree);
    if (tdir == NULL ||
	(tilde(edir, tdir) != 0) ||
	!(nd = dnormalize(edir->len ? edir->s : STRdot,
			  symlinks == SYM_IGNORE || symlinks == SYM_EXPAND)) ||
	((*dfd = opendir(short2str(nd))) == NULL)) {
	xfree(nd);
	if (cmd == SPELL || SearchNoDirErr) {
	    cleanup_until(tdir);
	    return (-2);
	}
	/*
	 * From: Amos Shapira <amoss@cs.huji.ac.il>
	 * Print a better message when completion fails
	 */
	xprintf("\n%S %s\n", edir->len ? edir->s : (tdir ? tdir : dir),
		(errno == ENOTDIR ? CGETS(30, 10, "not a directory") :
		(errno == ENOENT ? CGETS(30, 11, "not found") :
		 CGETS(30, 12, "unreadable"))));
	NeedsRedraw = 1;
	cleanup_until(tdir);
	return (-1);
    }
    cleanup_until(tdir);
    if (nd) {
	if (*dir != '\0') {
	    int slash;

	    /*
	     * Copy and append a / if there was one
	     */
	    slash = edir->len != 0 && edir->s[edir->len - 1] == '/';
	    edir->len = 0;
	    Strbuf_append(edir, nd);
	    if (slash != 0 && edir->s[edir->len - 1] != '/')
		Strbuf_append1(edir, '/');
	    Strbuf_terminate(edir);
	}
	xfree(nd);
    }
    return 0;
}