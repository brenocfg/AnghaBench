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
struct name {int dummy; } ;
struct header {char* h_subject; char* h_replyto; int /*<<< orphan*/ * h_inreplyto; struct name* h_smopts; struct name* h_bcc; struct name* h_cc; struct name* h_to; } ;

/* Variables and functions */
 int /*<<< orphan*/  mail1 (struct header*,int /*<<< orphan*/ ) ; 

int
mail(struct name *to, struct name *cc, struct name *bcc, struct name *smopts,
	char *subject, char *replyto)
{
	struct header head;

	head.h_to = to;
	head.h_subject = subject;
	head.h_cc = cc;
	head.h_bcc = bcc;
	head.h_smopts = smopts;
	head.h_replyto = replyto;
	head.h_inreplyto = NULL;
	mail1(&head, 0);
	return (0);
}