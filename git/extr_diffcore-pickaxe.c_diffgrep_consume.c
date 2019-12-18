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
struct diffgrep_cb {int hit; int /*<<< orphan*/  regexp; } ;
typedef  int /*<<< orphan*/  regmatch_t ;

/* Variables and functions */
 int /*<<< orphan*/  regexec_buf (int /*<<< orphan*/ ,char*,unsigned long,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void diffgrep_consume(void *priv, char *line, unsigned long len)
{
	struct diffgrep_cb *data = priv;
	regmatch_t regmatch;

	if (line[0] != '+' && line[0] != '-')
		return;
	if (data->hit)
		/*
		 * NEEDSWORK: we should have a way to terminate the
		 * caller early.
		 */
		return;
	data->hit = !regexec_buf(data->regexp, line + 1, len - 1, 1,
				 &regmatch, 0);
}