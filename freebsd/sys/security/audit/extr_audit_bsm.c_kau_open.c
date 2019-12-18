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
struct au_record {int used; scalar_t__ len; int /*<<< orphan*/  token_q; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_AUDITBSM ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 struct au_record* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct au_record *
kau_open(void)
{
	struct au_record *rec;

	rec = malloc(sizeof(*rec), M_AUDITBSM, M_WAITOK);
	rec->data = NULL;
	TAILQ_INIT(&rec->token_q);
	rec->len = 0;
	rec->used = 1;

	return (rec);
}