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
struct ifnet {int /*<<< orphan*/  if_ratelimit_query; int /*<<< orphan*/  if_snd_tag_free; int /*<<< orphan*/  if_snd_tag_query; int /*<<< orphan*/  if_snd_tag_modify; int /*<<< orphan*/  if_snd_tag_alloc; int /*<<< orphan*/  if_get_counter; int /*<<< orphan*/  if_transmit; int /*<<< orphan*/  if_qflush; int /*<<< orphan*/  if_resolvemulti; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_input; int /*<<< orphan*/  if_output; } ;

/* Variables and functions */
 int /*<<< orphan*/  ifdead_get_counter ; 
 int /*<<< orphan*/  ifdead_input ; 
 int /*<<< orphan*/  ifdead_ioctl ; 
 int /*<<< orphan*/  ifdead_output ; 
 int /*<<< orphan*/  ifdead_qflush ; 
 int /*<<< orphan*/  ifdead_ratelimit_query ; 
 int /*<<< orphan*/  ifdead_resolvemulti ; 
 int /*<<< orphan*/  ifdead_snd_tag_alloc ; 
 int /*<<< orphan*/  ifdead_snd_tag_free ; 
 int /*<<< orphan*/  ifdead_snd_tag_modify ; 
 int /*<<< orphan*/  ifdead_snd_tag_query ; 
 int /*<<< orphan*/  ifdead_start ; 
 int /*<<< orphan*/  ifdead_transmit ; 

void
if_dead(struct ifnet *ifp)
{

	ifp->if_output = ifdead_output;
	ifp->if_input = ifdead_input;
	ifp->if_start = ifdead_start;
	ifp->if_ioctl = ifdead_ioctl;
	ifp->if_resolvemulti = ifdead_resolvemulti;
	ifp->if_qflush = ifdead_qflush;
	ifp->if_transmit = ifdead_transmit;
	ifp->if_get_counter = ifdead_get_counter;
	ifp->if_snd_tag_alloc = ifdead_snd_tag_alloc;
	ifp->if_snd_tag_modify = ifdead_snd_tag_modify;
	ifp->if_snd_tag_query = ifdead_snd_tag_query;
	ifp->if_snd_tag_free = ifdead_snd_tag_free;
	ifp->if_ratelimit_query = ifdead_ratelimit_query;
}