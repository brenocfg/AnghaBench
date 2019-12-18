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
struct pt_query_decoder {int /*<<< orphan*/  config; int /*<<< orphan*/  pos; struct pt_decoder_function* next; } ;
struct pt_decoder_function {int dummy; } ;

/* Variables and functions */
 int pt_df_fetch (struct pt_decoder_function const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pte_eos ; 
 int pte_internal ; 

__attribute__((used)) static int pt_qry_will_eos(const struct pt_query_decoder *decoder)
{
	const struct pt_decoder_function *dfun;
	int errcode;

	if (!decoder)
		return -pte_internal;

	dfun = decoder->next;
	if (dfun)
		return 0;

	/* The decoding function may be NULL for two reasons:
	 *
	 *   - we ran out of trace
	 *   - we ran into a fetch error such as -pte_bad_opc
	 *
	 * Let's fetch again.
	 */
	errcode = pt_df_fetch(&dfun, decoder->pos, &decoder->config);
	return errcode == -pte_eos;
}