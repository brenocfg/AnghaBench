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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct index_state {int dummy; } ;
struct cache_entry {int /*<<< orphan*/  name; int /*<<< orphan*/  ce_mode; } ;

/* Variables and functions */
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 char* get_cached_convert_stats_ascii (struct index_state const*,int /*<<< orphan*/ ) ; 
 char* get_convert_attr_ascii (struct index_state const*,char const*) ; 
 char* get_wt_convert_stats_ascii (char const*) ; 
 int /*<<< orphan*/  lstat (char const*,struct stat*) ; 
 int /*<<< orphan*/  printf (char*,char const*,char const*,char const*) ; 
 scalar_t__ show_eol ; 

__attribute__((used)) static void write_eolinfo(const struct index_state *istate,
			  const struct cache_entry *ce, const char *path)
{
	if (show_eol) {
		struct stat st;
		const char *i_txt = "";
		const char *w_txt = "";
		const char *a_txt = get_convert_attr_ascii(istate, path);
		if (ce && S_ISREG(ce->ce_mode))
			i_txt = get_cached_convert_stats_ascii(istate,
							       ce->name);
		if (!lstat(path, &st) && S_ISREG(st.st_mode))
			w_txt = get_wt_convert_stats_ascii(path);
		printf("i/%-5s w/%-5s attr/%-17s\t", i_txt, w_txt, a_txt);
	}
}