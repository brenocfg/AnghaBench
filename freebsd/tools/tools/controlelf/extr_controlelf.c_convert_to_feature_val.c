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
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_3__ {int /*<<< orphan*/  value; int /*<<< orphan*/  alias; } ;

/* Variables and functions */
 TYPE_1__* featurelist ; 
 int nitems (TYPE_1__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static bool
convert_to_feature_val(char *feature_str, u_int32_t *feature_val)
{
	char *feature;
	int i, len;
	u_int32_t input;
	char operation;

	input = 0;
	operation = *feature_str;
	feature_str++;
	len = nitems(featurelist);
	while ((feature = strsep(&feature_str, ",")) != NULL) {
		for (i = 0; i < len; ++i) {
			if (strcmp(featurelist[i].alias, feature) == 0) {
				input |= featurelist[i].value;
				break;
			}
		}
		if (i == len) {
			warnx("%s is not a valid feature", feature);
			return (false);
		}
	}

	if (operation == '+') {
		*feature_val |= input;
	} else if (operation == '=') {
		*feature_val = input;
	} else if (operation == '-') {
		*feature_val &= ~input;
	} else {
		warnx("'%c' not an operator - use '+', '-', '='",
		    feature_str[0]);
		return (false);
	}
	return (true);
}