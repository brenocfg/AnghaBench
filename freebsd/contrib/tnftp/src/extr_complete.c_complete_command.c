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
struct cmd {char* c_name; } ;
typedef  int /*<<< orphan*/  StringList ;

/* Variables and functions */
 unsigned char CC_ERROR ; 
 unsigned char CC_REFRESH ; 
 struct cmd* cmdtab ; 
 unsigned char complete_ambiguous (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  el ; 
 int el_insertstr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ftp_sl_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ftp_sl_init () ; 
 int /*<<< orphan*/  ftp_strdup (char*) ; 
 int /*<<< orphan*/  sl_free (int /*<<< orphan*/ *,int) ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,size_t) ; 

__attribute__((used)) static unsigned char
complete_command(char *word, int list)
{
	struct cmd *c;
	StringList *words;
	size_t wordlen;
	unsigned char rv;

	words = ftp_sl_init();
	wordlen = strlen(word);

	for (c = cmdtab; c->c_name != NULL; c++) {
		if (wordlen > strlen(c->c_name))
			continue;
		if (strncmp(word, c->c_name, wordlen) == 0)
			ftp_sl_add(words, ftp_strdup(c->c_name));
	}

	rv = complete_ambiguous(word, list, words);
	if (rv == CC_REFRESH) {
		if (el_insertstr(el, " ") == -1)
			rv = CC_ERROR;
	}
	sl_free(words, 1);
	return (rv);
}