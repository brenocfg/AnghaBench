#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ kind; char* str; } ;
typedef  TYPE_1__ token ;

/* Variables and functions */
 scalar_t__ TOK_EOF ; 
 scalar_t__ TOK_IDENT ; 
 scalar_t__ isalnum (char) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 TYPE_1__* symbols ; 
 char* xmalloc (int) ; 

__attribute__((used)) static void
findkind(char **mark, token *tokp)
{
	int len;
	token *s;
	char *str, *tmp;

	str = *mark;
	for (s = symbols; s->kind != TOK_EOF; s++) {
		len = strlen(s->str);
		if (strncmp(str, s->str, len) == 0) {
			if (!isalnum(str[len]) && str[len] != '_') {
				tokp->kind = s->kind;
				tokp->str = s->str;
				*mark = str + len;
				return;
			}
		}
	}
	tokp->kind = TOK_IDENT;
	for (len = 0; isalnum(str[len]) || str[len] == '_'; len++);
	tmp = xmalloc(len + 1);
	(void) strlcpy(tmp, str, len + 1);
	tokp->str = tmp;
	*mark = str + len;
}