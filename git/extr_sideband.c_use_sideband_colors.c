#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct strbuf {char* buf; } ;
struct TYPE_3__ {int /*<<< orphan*/  color; int /*<<< orphan*/  keyword; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int GIT_COLOR_AUTO ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ color_parse (char*,int /*<<< orphan*/ ) ; 
 int git_config_colorbool (char const*,char*) ; 
 scalar_t__ git_config_get_string (char const*,char**) ; 
 TYPE_1__* keywords ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 

__attribute__((used)) static int use_sideband_colors(void)
{
	static int use_sideband_colors_cached = -1;

	const char *key = "color.remote";
	struct strbuf sb = STRBUF_INIT;
	char *value;
	int i;

	if (use_sideband_colors_cached >= 0)
		return use_sideband_colors_cached;

	if (!git_config_get_string(key, &value)) {
		use_sideband_colors_cached = git_config_colorbool(key, value);
	} else if (!git_config_get_string("color.ui", &value)) {
		use_sideband_colors_cached = git_config_colorbool("color.ui", value);
	} else {
		use_sideband_colors_cached = GIT_COLOR_AUTO;
	}

	for (i = 0; i < ARRAY_SIZE(keywords); i++) {
		strbuf_reset(&sb);
		strbuf_addf(&sb, "%s.%s", key, keywords[i].keyword);
		if (git_config_get_string(sb.buf, &value))
			continue;
		if (color_parse(value, keywords[i].color))
			continue;
	}
	strbuf_release(&sb);
	return use_sideband_colors_cached;
}