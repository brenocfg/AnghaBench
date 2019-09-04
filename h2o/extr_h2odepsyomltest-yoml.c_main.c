#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int size; TYPE_2__* elements; } ;
struct TYPE_10__ {int size; TYPE_5__** elements; } ;
struct TYPE_13__ {int /*<<< orphan*/  scalar; TYPE_3__ mapping; TYPE_1__ sequence; } ;
struct TYPE_14__ {scalar_t__ type; int _refcnt; TYPE_4__ data; int /*<<< orphan*/  filename; } ;
typedef  TYPE_5__ yoml_t ;
struct TYPE_11__ {TYPE_5__* value; TYPE_5__* key; } ;

/* Variables and functions */
 scalar_t__ YOML_TYPE_MAPPING ; 
 scalar_t__ YOML_TYPE_SCALAR ; 
 scalar_t__ YOML_TYPE_SEQUENCE ; 
 int done_testing () ; 
 TYPE_5__* get_value (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  ok (int) ; 
 TYPE_5__* parse (char*,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  yoml_free (TYPE_5__*,int /*<<< orphan*/ *) ; 

int main(int argc, char **argv)
{
    yoml_t *doc, *t;
    size_t i;

    doc = parse("foo.yaml", "abc");
    ok(doc != NULL);
    ok(strcmp(doc->filename, "foo.yaml") == 0);
    ok(doc->type == YOML_TYPE_SCALAR);
    ok(strcmp(doc->data.scalar, "abc") == 0);
    yoml_free(doc, NULL);

    doc = parse(
       "foo.yaml",
        "---\n"
        "a: b\n"
        "c: d\n"
        "---\n"
        "e: f\n");
    ok(doc != NULL);
    ok(strcmp(doc->filename, "foo.yaml") == 0);
    ok(doc->type == YOML_TYPE_MAPPING);
    ok(doc->data.mapping.size == 2);
    t = doc->data.mapping.elements[0].key;
    ok(strcmp(t->filename, "foo.yaml") == 0);
    ok(t->type == YOML_TYPE_SCALAR);
    ok(strcmp(t->data.scalar, "a") == 0);
    t = doc->data.mapping.elements[0].value;
    ok(strcmp(t->filename, "foo.yaml") == 0);
    ok(t->type == YOML_TYPE_SCALAR);
    ok(strcmp(t->data.scalar, "b") == 0);
    t = doc->data.mapping.elements[1].key;
    ok(strcmp(t->filename, "foo.yaml") == 0);
    ok(t->type == YOML_TYPE_SCALAR);
    ok(strcmp(t->data.scalar, "c") == 0);
    t = doc->data.mapping.elements[1].value;
    ok(strcmp(t->filename, "foo.yaml") == 0);
    ok(t->type == YOML_TYPE_SCALAR);
    ok(strcmp(t->data.scalar, "d") == 0);
    yoml_free(doc, NULL);

    doc = parse(
            "bar.yaml",
            "- a: b\n"
            "  c: d\n"
            "- e\n");
    ok(doc != NULL);
    ok(strcmp(doc->filename, "bar.yaml") == 0);
    ok(doc->type == YOML_TYPE_SEQUENCE);
    ok(doc->data.sequence.size == 2);
    t = doc->data.sequence.elements[0];
    ok(strcmp(doc->filename, "bar.yaml") == 0);
    ok(t->type == YOML_TYPE_MAPPING);
    ok(t->data.mapping.size == 2);
    t = doc->data.sequence.elements[0]->data.mapping.elements[0].key;
    ok(strcmp(doc->filename, "bar.yaml") == 0);
    ok(t->type == YOML_TYPE_SCALAR);
    ok(strcmp(t->data.scalar, "a") == 0);
    t = doc->data.sequence.elements[0]->data.mapping.elements[0].value;
    ok(strcmp(doc->filename, "bar.yaml") == 0);
    ok(t->type == YOML_TYPE_SCALAR);
    ok(strcmp(t->data.scalar, "b") == 0);
    t = doc->data.sequence.elements[0]->data.mapping.elements[1].key;
    ok(strcmp(doc->filename, "bar.yaml") == 0);
    ok(t->type == YOML_TYPE_SCALAR);
    ok(strcmp(t->data.scalar, "c") == 0);
    t = doc->data.sequence.elements[0]->data.mapping.elements[1].value;
    ok(strcmp(doc->filename, "bar.yaml") == 0);
    ok(t->type == YOML_TYPE_SCALAR);
    ok(strcmp(t->data.scalar, "d") == 0);
    t = doc->data.sequence.elements[1];
    ok(strcmp(doc->filename, "bar.yaml") == 0);
    ok(t->type == YOML_TYPE_SCALAR);
    ok(strcmp(t->data.scalar, "e") == 0);
    yoml_free(doc, NULL);

    doc = parse(
        "baz.yaml",
        "- &abc\n"
        "  - 1\n"
        "  - 2\n"
        "- *abc\n");
    ok(doc != NULL);
    ok(strcmp(doc->filename, "baz.yaml") == 0);
    ok(doc->type == YOML_TYPE_SEQUENCE);
    ok(doc->data.sequence.size == 2);
    ok(doc->data.sequence.elements[0] == doc->data.sequence.elements[1]);
    t = doc->data.sequence.elements[0];
    ok(strcmp(t->filename, "baz.yaml") == 0);
    ok(t->_refcnt == 2);
    ok(t->type == YOML_TYPE_SEQUENCE);
    ok(t->data.sequence.size == 2);
    t = doc->data.sequence.elements[0]->data.sequence.elements[0];
    ok(strcmp(t->filename, "baz.yaml") == 0);
    ok(t->type == YOML_TYPE_SCALAR);
    ok(strcmp(t->data.scalar, "1") == 0);
    t = doc->data.sequence.elements[0]->data.sequence.elements[1];
    ok(strcmp(t->filename, "baz.yaml") == 0);
    ok(t->type == YOML_TYPE_SCALAR);
    ok(strcmp(t->data.scalar, "2") == 0);

    doc = parse(
        "foo.yaml",
        "- &link\n"
        "  x: 1\n"
        "  y: 2\n"
        "- <<: *link\n"
        "  y: 3\n");
    ok(doc != NULL);
    ok(doc->type == YOML_TYPE_SEQUENCE);
    ok(doc->data.sequence.size == 2);
    ok(doc->data.sequence.elements[0]->type == YOML_TYPE_MAPPING);
    ok(doc->data.sequence.elements[0]->data.mapping.size == 2);
    ok(doc->data.sequence.elements[0]->data.mapping.elements[0].key->type == YOML_TYPE_SCALAR);
    ok(strcmp(doc->data.sequence.elements[0]->data.mapping.elements[0].key->data.scalar, "x") == 0);
    ok(doc->data.sequence.elements[0]->data.mapping.elements[0].value->type == YOML_TYPE_SCALAR);
    ok(strcmp(doc->data.sequence.elements[0]->data.mapping.elements[0].value->data.scalar, "1") == 0);
    ok(doc->data.sequence.elements[0]->data.mapping.elements[1].key->type == YOML_TYPE_SCALAR);
    ok(strcmp(doc->data.sequence.elements[0]->data.mapping.elements[1].key->data.scalar, "y") == 0);
    ok(doc->data.sequence.elements[0]->data.mapping.elements[1].value->type == YOML_TYPE_SCALAR);
    ok(strcmp(doc->data.sequence.elements[0]->data.mapping.elements[1].value->data.scalar, "2") == 0);
    ok(doc->data.sequence.elements[1]->data.mapping.elements[0].key->type == YOML_TYPE_SCALAR);
    ok(strcmp(doc->data.sequence.elements[1]->data.mapping.elements[0].key->data.scalar, "x") == 0);
    ok(doc->data.sequence.elements[1]->data.mapping.elements[0].value->type == YOML_TYPE_SCALAR);
    ok(strcmp(doc->data.sequence.elements[1]->data.mapping.elements[0].value->data.scalar, "1") == 0);
    ok(doc->data.sequence.elements[1]->data.mapping.elements[1].key->type == YOML_TYPE_SCALAR);
    ok(strcmp(doc->data.sequence.elements[1]->data.mapping.elements[1].key->data.scalar, "y") == 0);
    ok(doc->data.sequence.elements[1]->data.mapping.elements[1].value->type == YOML_TYPE_SCALAR);
    ok(strcmp(doc->data.sequence.elements[1]->data.mapping.elements[1].value->data.scalar, "3") == 0);

    doc = parse(
        "foo.yaml",
        "- &CENTER { x: 1, y: 2 }\n"
        "- &LEFT { x: 0, y: 2 }\n"
        "- &BIG { r: 10 }\n"
        "- &SMALL { r: 1 }\n"
        "- # Explicit keys\n"
        "  x: 1\n"
        "  y: 2\n"
        "  r: 10\n"
        "- # Merge one map\n"
        "  << : *CENTER\n"
        "  r: 10\n"
        "- # Merge multiple maps\n"
        "  << : [ *CENTER, *BIG ]\n"
        "- # Override\n"
        "  << : [ *BIG, *LEFT, *SMALL ]\n"
        "  x: 1\n");
    ok(doc != NULL);
    ok(doc->type == YOML_TYPE_SEQUENCE);
    for (i = 4; i <= 7; ++i) {
        ok(doc->data.sequence.elements[i]->type == YOML_TYPE_MAPPING);
        ok(doc->data.sequence.elements[i]->data.mapping.size == 3);
        t = get_value(doc->data.sequence.elements[i], "x");
        ok(t != NULL);
        ok(t->type == YOML_TYPE_SCALAR);
        ok(strcmp(t->data.scalar, "1") == 0);
        t = get_value(doc->data.sequence.elements[i], "y");
        ok(t != NULL);
        ok(t->type == YOML_TYPE_SCALAR);
        ok(strcmp(t->data.scalar, "2") == 0);
        t = get_value(doc->data.sequence.elements[i], "r");
        ok(t != NULL);
        ok(t->type == YOML_TYPE_SCALAR);
        ok(strcmp(t->data.scalar, "10") == 0);
    }

    doc = parse(
        "foo.yaml",
        "- &link\n"
        "  x: 1\n"
        "  x: 2\n"
        "-\n"
        "  x: 3\n"
        "  <<: *link\n");
    ok(doc != NULL);
    ok(doc->type == YOML_TYPE_SEQUENCE);
    ok(doc->data.sequence.size == 2);
    ok(doc->data.sequence.elements[0]->type == YOML_TYPE_MAPPING);
    ok(doc->data.sequence.elements[0]->data.mapping.size == 2);
    ok(doc->data.sequence.elements[0]->data.mapping.elements[0].key->type == YOML_TYPE_SCALAR);
    ok(strcmp(doc->data.sequence.elements[0]->data.mapping.elements[0].key->data.scalar, "x") == 0);
    ok(doc->data.sequence.elements[0]->data.mapping.elements[0].value->type == YOML_TYPE_SCALAR);
    ok(strcmp(doc->data.sequence.elements[0]->data.mapping.elements[0].value->data.scalar, "1") == 0);
    ok(doc->data.sequence.elements[0]->data.mapping.elements[1].key->type == YOML_TYPE_SCALAR);
    ok(strcmp(doc->data.sequence.elements[0]->data.mapping.elements[1].key->data.scalar, "x") == 0);
    ok(doc->data.sequence.elements[0]->data.mapping.elements[1].value->type == YOML_TYPE_SCALAR);
    ok(strcmp(doc->data.sequence.elements[0]->data.mapping.elements[1].value->data.scalar, "2") == 0);
    ok(doc->data.sequence.elements[1]->data.mapping.size == 3);
    ok(doc->data.sequence.elements[1]->data.mapping.elements[0].key->type == YOML_TYPE_SCALAR);
    ok(strcmp(doc->data.sequence.elements[1]->data.mapping.elements[0].key->data.scalar, "x") == 0);
    ok(doc->data.sequence.elements[1]->data.mapping.elements[0].value->type == YOML_TYPE_SCALAR);
    ok(strcmp(doc->data.sequence.elements[1]->data.mapping.elements[0].value->data.scalar, "3") == 0);
    ok(doc->data.sequence.elements[1]->data.mapping.elements[1].key->type == YOML_TYPE_SCALAR);
    ok(strcmp(doc->data.sequence.elements[1]->data.mapping.elements[1].key->data.scalar, "x") == 0);
    ok(doc->data.sequence.elements[1]->data.mapping.elements[1].value->type == YOML_TYPE_SCALAR);
    ok(strcmp(doc->data.sequence.elements[1]->data.mapping.elements[1].value->data.scalar, "1") == 0);
    ok(doc->data.sequence.elements[1]->data.mapping.elements[2].key->type == YOML_TYPE_SCALAR);
    ok(strcmp(doc->data.sequence.elements[1]->data.mapping.elements[2].key->data.scalar, "x") == 0);
    ok(doc->data.sequence.elements[1]->data.mapping.elements[2].value->type == YOML_TYPE_SCALAR);
    ok(strcmp(doc->data.sequence.elements[1]->data.mapping.elements[2].value->data.scalar, "2") == 0);

    doc = parse(
        "foo.yaml",
        "a: &link1\n"
        " x: 1\n"
        "b: &link2\n"
        " <<: *link1\n"
        " y: 2\n"
        "c:\n"
        " <<: *link2\n"
    );
    ok(doc != NULL);
    ok(doc->type == YOML_TYPE_MAPPING);
    ok(doc->data.mapping.size == 3);
    ok(doc->data.mapping.elements[2].value->type == YOML_TYPE_MAPPING);
    ok(doc->data.mapping.elements[2].value->data.mapping.size == 2);
    ok(doc->data.mapping.elements[2].value->data.mapping.elements[0].key->type == YOML_TYPE_SCALAR);
    ok(strcmp(doc->data.mapping.elements[2].value->data.mapping.elements[0].key->data.scalar, "x") == 0);
    ok(doc->data.mapping.elements[2].value->data.mapping.elements[0].value->type == YOML_TYPE_SCALAR);
    ok(strcmp(doc->data.mapping.elements[2].value->data.mapping.elements[0].value->data.scalar, "1") == 0);
    ok(doc->data.mapping.elements[2].value->data.mapping.elements[1].key->type == YOML_TYPE_SCALAR);
    ok(strcmp(doc->data.mapping.elements[2].value->data.mapping.elements[1].key->data.scalar, "y") == 0);
    ok(doc->data.mapping.elements[2].value->data.mapping.elements[1].value->type == YOML_TYPE_SCALAR);
    ok(strcmp(doc->data.mapping.elements[2].value->data.mapping.elements[1].value->data.scalar, "2") == 0);

    return done_testing();
}