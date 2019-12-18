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
struct pt_query_decoder {int /*<<< orphan*/  evq; int /*<<< orphan*/  tcal; int /*<<< orphan*/  last_time; int /*<<< orphan*/  time; int /*<<< orphan*/  tnt; int /*<<< orphan*/  ip; int /*<<< orphan*/  config; } ;
struct pt_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct pt_query_decoder*,int /*<<< orphan*/ ,int) ; 
 int pt_config_from_user (int /*<<< orphan*/ *,struct pt_config const*) ; 
 int /*<<< orphan*/  pt_evq_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pt_last_ip_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pt_tcal_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pt_time_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pt_tnt_cache_init (int /*<<< orphan*/ *) ; 
 int pte_invalid ; 

int pt_qry_decoder_init(struct pt_query_decoder *decoder,
			const struct pt_config *config)
{
	int errcode;

	if (!decoder)
		return -pte_invalid;

	memset(decoder, 0, sizeof(*decoder));

	errcode = pt_config_from_user(&decoder->config, config);
	if (errcode < 0)
		return errcode;

	pt_last_ip_init(&decoder->ip);
	pt_tnt_cache_init(&decoder->tnt);
	pt_time_init(&decoder->time);
	pt_time_init(&decoder->last_time);
	pt_tcal_init(&decoder->tcal);
	pt_evq_init(&decoder->evq);

	return 0;
}