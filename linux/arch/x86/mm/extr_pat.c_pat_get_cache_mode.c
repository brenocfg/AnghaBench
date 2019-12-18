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
typedef  enum page_cache_mode { ____Placeholder_page_cache_mode } page_cache_mode ;

/* Variables and functions */
 int CM (int /*<<< orphan*/ ) ; 
#define  PAT_UC 133 
#define  PAT_UC_MINUS 132 
#define  PAT_WB 131 
#define  PAT_WC 130 
#define  PAT_WP 129 
#define  PAT_WT 128 
 int /*<<< orphan*/  UC ; 
 int /*<<< orphan*/  UC_MINUS ; 
 int /*<<< orphan*/  WB ; 
 int /*<<< orphan*/  WC ; 
 int /*<<< orphan*/  WP ; 
 int /*<<< orphan*/  WT ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static enum page_cache_mode pat_get_cache_mode(unsigned pat_val, char *msg)
{
	enum page_cache_mode cache;
	char *cache_mode;

	switch (pat_val) {
	case PAT_UC:       cache = CM(UC);       cache_mode = "UC  "; break;
	case PAT_WC:       cache = CM(WC);       cache_mode = "WC  "; break;
	case PAT_WT:       cache = CM(WT);       cache_mode = "WT  "; break;
	case PAT_WP:       cache = CM(WP);       cache_mode = "WP  "; break;
	case PAT_WB:       cache = CM(WB);       cache_mode = "WB  "; break;
	case PAT_UC_MINUS: cache = CM(UC_MINUS); cache_mode = "UC- "; break;
	default:           cache = CM(WB);       cache_mode = "WB  "; break;
	}

	memcpy(msg, cache_mode, 4);

	return cache;
}