#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* data; int /*<<< orphan*/  length; } ;
struct TYPE_5__ {TYPE_1__ reply; int /*<<< orphan*/  prompt; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ hx509_prompt ;

/* Variables and functions */
 scalar_t__ UI_UTIL_read_pw_string (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hx509_prompt_hidden (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 size_t strcspn (char*,char*) ; 

__attribute__((used)) static int
default_prompter(void *data, const hx509_prompt *prompter)
{
    if (hx509_prompt_hidden(prompter->type)) {
	if(UI_UTIL_read_pw_string(prompter->reply.data,
				  prompter->reply.length,
				  prompter->prompt,
				  0))
	    return 1;
    } else {
	char *s = prompter->reply.data;

	fputs (prompter->prompt, stdout);
	fflush (stdout);
	if(fgets(prompter->reply.data,
		 prompter->reply.length,
		 stdin) == NULL)
	    return 1;
	s[strcspn(s, "\n")] = '\0';
    }
    return 0;
}