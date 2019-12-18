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
struct header {int /*<<< orphan*/ * h_inreplyto; int /*<<< orphan*/  h_replyto; int /*<<< orphan*/ * h_smopts; int /*<<< orphan*/ * h_bcc; int /*<<< orphan*/ * h_cc; int /*<<< orphan*/ * h_subject; int /*<<< orphan*/  h_to; } ;

/* Variables and functions */
 int /*<<< orphan*/  GTO ; 
 int /*<<< orphan*/  extract (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mail1 (struct header*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value (char*) ; 

int
sendmail(char *str)
{
	struct header head;

	head.h_to = extract(str, GTO);
	head.h_subject = NULL;
	head.h_cc = NULL;
	head.h_bcc = NULL;
	head.h_smopts = NULL;
	head.h_replyto = value("REPLYTO");
	head.h_inreplyto = NULL;
	mail1(&head, 0);
	return (0);
}