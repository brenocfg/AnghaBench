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
struct ptunit_result {int dummy; } ;
struct pt_query_decoder {int enabled; int /*<<< orphan*/  config; int /*<<< orphan*/  pos; int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  pt_df_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_ptr (struct pt_query_decoder*) ; 

__attribute__((used)) static struct ptunit_result ptu_sync_decoder(struct pt_query_decoder *decoder)
{
	ptu_ptr(decoder);
	decoder->enabled = 1;

	(void) pt_df_fetch(&decoder->next, decoder->pos, &decoder->config);
	return ptu_passed();
}