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
typedef  int /*<<< orphan*/  JSON_Status ;
typedef  int /*<<< orphan*/  JSON_Object ;

/* Variables and functions */
 int /*<<< orphan*/  JSONFailure ; 
 int /*<<< orphan*/ * json_object_get_object (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  json_object_remove (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  parson_free (char*) ; 
 char* parson_strndup (char const*,int) ; 
 char* strchr (char const*,char) ; 

JSON_Status json_object_dotremove(JSON_Object *object, const char *name) {
    const char *dot_pos = strchr(name, '.');
    char *current_name = NULL;
    JSON_Object *temp_obj = NULL;
    if (dot_pos == NULL) {
        return json_object_remove(object, name);
    } else {
        current_name = parson_strndup(name, dot_pos - name);
        temp_obj = json_object_get_object(object, current_name);
        parson_free(current_name);
        if (temp_obj == NULL) {
            return JSONFailure;
        }
        return json_object_dotremove(temp_obj, dot_pos + 1);
    }
}