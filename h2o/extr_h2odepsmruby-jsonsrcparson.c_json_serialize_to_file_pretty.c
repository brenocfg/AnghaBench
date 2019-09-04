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
typedef  int /*<<< orphan*/  JSON_Value ;
typedef  int /*<<< orphan*/  JSON_Status ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int /*<<< orphan*/  JSONFailure ; 
 int /*<<< orphan*/  JSONSuccess ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_free_serialized_string (char*) ; 
 char* json_serialize_to_string_pretty (int /*<<< orphan*/  const*) ; 

JSON_Status json_serialize_to_file_pretty(const JSON_Value *value, const char *filename) {
    JSON_Status return_code = JSONSuccess;
    FILE *fp = NULL;
    char *serialized_string = json_serialize_to_string_pretty(value);
    if (serialized_string == NULL) {
        return JSONFailure;
    }
    fp = fopen(filename, "w");
    if (fp == NULL) {
        json_free_serialized_string(serialized_string);
        return JSONFailure;
    }
    if (fputs(serialized_string, fp) == EOF) {
        return_code = JSONFailure;
    }
    if (fclose(fp) == EOF) {
        return_code = JSONFailure;
    }
    json_free_serialized_string(serialized_string);
    return return_code;
}