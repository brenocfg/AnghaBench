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
struct pt_query_decoder {int /*<<< orphan*/  config; int /*<<< orphan*/  pos; } ;
struct pt_decoder_function {int dummy; } ;

/* Variables and functions */
 int pt_df_fetch (struct pt_decoder_function const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pte_internal ; 

__attribute__((used)) static int pt_qry_provoke_fetch_error(const struct pt_query_decoder *decoder)
{
	const struct pt_decoder_function *dfun;
	int errcode;

	if (!decoder)
		return -pte_internal;

	/* Repeat the decoder fetch to reproduce the error. */
	errcode = pt_df_fetch(&dfun, decoder->pos, &decoder->config);
	if (errcode < 0)
		return errcode;

	/* We must get some error or something's wrong. */
	return -pte_internal;
}