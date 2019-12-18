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
struct mc_proxy_merge_conf {int use_at; } ;

/* Variables and functions */
 struct mc_proxy_merge_conf* get_extension_conf () ; 

int use_at () {
  struct mc_proxy_merge_conf *conf = get_extension_conf ();
  return conf->use_at;
}