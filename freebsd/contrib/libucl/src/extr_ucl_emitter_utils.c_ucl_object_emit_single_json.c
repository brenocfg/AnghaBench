#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* sv; int /*<<< orphan*/  iv; int /*<<< orphan*/  dv; } ;
struct TYPE_5__ {int type; int len; TYPE_1__ value; } ;
typedef  TYPE_2__ ucl_object_t ;
typedef  int /*<<< orphan*/  UT_string ;

/* Variables and functions */
#define  UCL_ARRAY 136 
#define  UCL_BOOLEAN 135 
#define  UCL_FLOAT 134 
#define  UCL_INT 133 
#define  UCL_NULL 132 
#define  UCL_OBJECT 131 
#define  UCL_STRING 130 
#define  UCL_TIME 129 
#define  UCL_USERDATA 128 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucl_utstring_append_double (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucl_utstring_append_int (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucl_utstring_append_len (char*,int,int /*<<< orphan*/ *) ; 
 unsigned char* utstring_body (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  utstring_new (int /*<<< orphan*/ *) ; 

unsigned char *
ucl_object_emit_single_json (const ucl_object_t *obj)
{
	UT_string *buf = NULL;
	unsigned char *res = NULL;

	if (obj == NULL) {
		return NULL;
	}

	utstring_new (buf);

	if (buf != NULL) {
		switch (obj->type) {
		case UCL_OBJECT:
			ucl_utstring_append_len ("object", 6, buf);
			break;
		case UCL_ARRAY:
			ucl_utstring_append_len ("array", 5, buf);
			break;
		case UCL_INT:
			ucl_utstring_append_int (obj->value.iv, buf);
			break;
		case UCL_FLOAT:
		case UCL_TIME:
			ucl_utstring_append_double (obj->value.dv, buf);
			break;
		case UCL_NULL:
			ucl_utstring_append_len ("null", 4, buf);
			break;
		case UCL_BOOLEAN:
			if (obj->value.iv) {
				ucl_utstring_append_len ("true", 4, buf);
			}
			else {
				ucl_utstring_append_len ("false", 5, buf);
			}
			break;
		case UCL_STRING:
			ucl_utstring_append_len (obj->value.sv, obj->len, buf);
			break;
		case UCL_USERDATA:
			ucl_utstring_append_len ("userdata", 8, buf);
			break;
		}
		res = utstring_body (buf);
		free (buf);
	}

	return res;
}