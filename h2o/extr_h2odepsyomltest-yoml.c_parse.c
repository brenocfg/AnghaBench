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
typedef  int /*<<< orphan*/  yoml_t ;
typedef  int /*<<< orphan*/  yaml_parser_t ;
typedef  int /*<<< orphan*/  yaml_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  yaml_parser_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yaml_parser_initialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yaml_parser_set_input_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * yoml_parse_document (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static yoml_t *parse(const char *fn, const char *s)
{
    yaml_parser_t parser;
    yoml_t *doc;

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, (yaml_char_t*)s, strlen(s));
    doc = yoml_parse_document(&parser, NULL, NULL, fn);
    yaml_parser_delete(&parser);

    return doc;
}