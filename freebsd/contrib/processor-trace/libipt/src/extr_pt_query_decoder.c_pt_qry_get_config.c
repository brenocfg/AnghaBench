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
struct pt_config {int dummy; } ;
struct pt_query_decoder {struct pt_config const config; } ;

/* Variables and functions */

const struct pt_config *
pt_qry_get_config(const struct pt_query_decoder *decoder)
{
	if (!decoder)
		return NULL;

	return &decoder->config;
}