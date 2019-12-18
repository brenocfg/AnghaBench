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
struct mc_proxy_merge_functions {int dummy; } ;

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
 struct mc_proxy_merge_functions default_merge_functions ; 
 struct mc_proxy_merge_functions friends_extension_functions ; 
 struct mc_proxy_merge_functions hints_merge_extension_functions ; 
 struct mc_proxy_merge_functions news_comm_extension_functions ; 
 struct mc_proxy_merge_functions news_ug_extension_functions ; 
 struct mc_proxy_merge_functions newsr_extension_functions ; 
 struct mc_proxy_merge_functions random_merge_extension_functions ; 
 struct mc_proxy_merge_functions search_extension_functions ; 
 struct mc_proxy_merge_functions searchx_extension_functions ; 
 struct mc_proxy_merge_functions statsx_extension_functions ; 
 struct mc_proxy_merge_functions targ_extension_functions ; 

struct mc_proxy_merge_functions *get_extension_functions () {
  if (SEARCH_EXTENSION) {
    return &search_extension_functions;
  } else if (SEARCHX_EXTENSION) {
    return &searchx_extension_functions;
  } else if (TARG_EXTENSION) {
    return &targ_extension_functions;
  } else if (NEWS_UG_EXTENSION) {  
    return &news_ug_extension_functions;
  } else if (NEWS_G_EXTENSION) {  
    return &news_ug_extension_functions;
  } else if (NEWS_COMM_EXTENSION) {
    return &news_comm_extension_functions;
  } else if (STATSX_EXTENSION) {
    return &statsx_extension_functions;
  } else if (FRIENDS_EXTENSION) {
    return &friends_extension_functions;
  } else if (HINTS_MERGE_EXTENSION) {
    return &hints_merge_extension_functions;
  } else if (NEWSR_EXTENSION) {
    return &newsr_extension_functions;
  } else if (RANDOM_MERGE_EXTENSION) {
    return &random_merge_extension_functions;
  } else {  
    return &default_merge_functions;
  }
}