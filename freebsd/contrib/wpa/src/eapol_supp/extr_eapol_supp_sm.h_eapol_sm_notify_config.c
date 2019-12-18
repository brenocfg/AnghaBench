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
struct eapol_sm {int dummy; } ;
struct eapol_config {int dummy; } ;
struct eap_peer_config {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void eapol_sm_notify_config(struct eapol_sm *sm,
					  struct eap_peer_config *config,
					  struct eapol_config *conf)
{
}