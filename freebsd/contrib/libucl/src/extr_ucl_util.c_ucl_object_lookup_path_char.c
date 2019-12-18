#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int type; } ;
typedef  TYPE_1__ ucl_object_t ;

/* Variables and functions */
#define  UCL_ARRAY 128 
 unsigned int strtoul (char const*,char**,int) ; 
 TYPE_1__* ucl_array_find_index (TYPE_1__ const*,unsigned int) ; 
 TYPE_1__* ucl_object_lookup_len (TYPE_1__ const*,char const*,int) ; 

const ucl_object_t *
ucl_object_lookup_path_char (const ucl_object_t *top, const char *path_in, const char sep) {
	const ucl_object_t *o = NULL, *found;
	const char *p, *c;
	char *err_str;
	unsigned index;

	if (path_in == NULL || top == NULL) {
		return NULL;
	}

	found = NULL;
	p = path_in;

	/* Skip leading dots */
	while (*p == sep) {
		p ++;
	}

	c = p;
	while (*p != '\0') {
		p ++;
		if (*p == sep || *p == '\0') {
			if (p > c) {
				switch (top->type) {
				case UCL_ARRAY:
					/* Key should be an int */
					index = strtoul (c, &err_str, 10);
					if (err_str != NULL && (*err_str != sep && *err_str != '\0')) {
						return NULL;
					}
					o = ucl_array_find_index (top, index);
					break;
				default:
					o = ucl_object_lookup_len (top, c, p - c);
					break;
				}
				if (o == NULL) {
					return NULL;
				}
				top = o;
			}
			if (*p != '\0') {
				c = p + 1;
			}
		}
	}
	found = o;

	return found;
}