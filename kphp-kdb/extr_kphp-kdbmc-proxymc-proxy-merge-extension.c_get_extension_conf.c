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
struct mc_proxy_merge_conf {int dummy; } ;

/* Variables and functions */
 scalar_t__ FRIENDS_EXTENSION ; 
 scalar_t__ HINTS_MERGE_EXTENSION ; 
 scalar_t__ NEWSR_EXTENSION ; 
 scalar_t__ NEWS_COMM_EXTENSION ; 
 scalar_t__ NEWS_G_EXTENSION ; 
 scalar_t__ NEWS_UG_EXTENSION ; 
 scalar_t__ RANDOM_MERGE_EXTENSION ; 
 scalar_t__ SEARCHX_EXTENSION ; 
 scalar_t__ SEARCH_EXTENSION ; 
 scalar_t__ STATSX_EXTENSION ; 
 scalar_t__ TARG_EXTENSION ; 
 struct mc_proxy_merge_conf default_merge_conf ; 
 struct mc_proxy_merge_conf friends_extension_conf ; 
 struct mc_proxy_merge_conf hints_merge_extension_conf ; 
 struct mc_proxy_merge_conf news_comm_extension_conf ; 
 struct mc_proxy_merge_conf news_ug_extension_conf ; 
 struct mc_proxy_merge_conf newsr_extension_conf ; 
 struct mc_proxy_merge_conf random_merge_extension_conf ; 
 struct mc_proxy_merge_conf search_extension_conf ; 
 struct mc_proxy_merge_conf searchx_extension_conf ; 
 struct mc_proxy_merge_conf statsx_extension_conf ; 
 struct mc_proxy_merge_conf targ_extension_conf ; 

struct mc_proxy_merge_conf *get_extension_conf () {
  if (SEARCH_EXTENSION) {
    return &search_extension_conf;
  } else if (SEARCHX_EXTENSION) {
    return &searchx_extension_conf;
  } else if (TARG_EXTENSION) {
    return &targ_extension_conf;
  } else if (NEWS_UG_EXTENSION) {  
    return &news_ug_extension_conf;
  } else if (NEWS_G_EXTENSION) {  
    return &news_ug_extension_conf;
  } else if (NEWS_COMM_EXTENSION) {
    return &news_comm_extension_conf;
  } else if (STATSX_EXTENSION) {
    return &statsx_extension_conf;
  } else if (FRIENDS_EXTENSION) {
    return &friends_extension_conf;
  } else if (HINTS_MERGE_EXTENSION) {
    return &hints_merge_extension_conf;
  } else if (NEWSR_EXTENSION) {
    return &newsr_extension_conf;
  } else if (RANDOM_MERGE_EXTENSION) {
    return &random_merge_extension_conf;
  } else {
    return &default_merge_conf;
  }
}