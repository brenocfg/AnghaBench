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
struct eap_identity_data {scalar_t__ state; } ;
typedef  int Boolean ;

/* Variables and functions */
 scalar_t__ CONTINUE ; 

__attribute__((used)) static Boolean eap_identity_isDone(struct eap_sm *sm, void *priv)
{
	struct eap_identity_data *data = priv;
	return data->state != CONTINUE;
}