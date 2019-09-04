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
struct tr2_cfg_data {int /*<<< orphan*/  line; int /*<<< orphan*/  file; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM_CASEFOLD ; 
 int WM_MATCH ; 
 struct strbuf** tr2_cfg_patterns ; 
 int /*<<< orphan*/  trace2_def_param_fl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*) ; 
 int wildmatch (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tr2_cfg_cb(const char *key, const char *value, void *d)
{
	struct strbuf **s;
	struct tr2_cfg_data *data = (struct tr2_cfg_data *)d;

	for (s = tr2_cfg_patterns; *s; s++) {
		struct strbuf *buf = *s;
		int wm = wildmatch(buf->buf, key, WM_CASEFOLD);
		if (wm == WM_MATCH) {
			trace2_def_param_fl(data->file, data->line, key, value);
			return 0;
		}
	}

	return 0;
}