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
struct eap_sm {int dummy; } ;
struct eap_fast_data {int dummy; } ;
typedef  int /*<<< orphan*/  EapType ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_TYPE_NONE ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  eap_fast_state (struct eap_fast_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static EapType eap_fast_req_failure(struct eap_sm *sm,
				    struct eap_fast_data *data)
{
	/* TODO: send Result TLV(FAILURE) */
	eap_fast_state(data, FAILURE);
	return EAP_TYPE_NONE;
}