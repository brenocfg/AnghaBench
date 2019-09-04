#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nasty ;
struct TYPE_38__ {void* ptr; } ;
struct TYPE_39__ {TYPE_1__ u; } ;
typedef  TYPE_2__ jv ;
typedef  int /*<<< orphan*/  big ;

/* Variables and functions */
 scalar_t__ JV_KIND_ARRAY ; 
 scalar_t__ JV_KIND_INVALID ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__ jv_array () ; 
 TYPE_2__ jv_array_append (TYPE_2__,TYPE_2__) ; 
 TYPE_2__ jv_array_get (TYPE_2__,int) ; 
 int jv_array_length (TYPE_2__) ; 
 TYPE_2__ jv_array_slice (TYPE_2__,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ jv_copy (TYPE_2__) ; 
 int jv_equal (TYPE_2__,TYPE_2__) ; 
 int /*<<< orphan*/  jv_free (TYPE_2__) ; 
 scalar_t__ jv_get_kind (TYPE_2__) ; 
 int jv_get_refcnt (TYPE_2__) ; 
 TYPE_2__ jv_invalid_get_msg (TYPE_2__) ; 
 TYPE_2__ jv_number (int) ; 
 int jv_number_value (TYPE_2__) ; 
 TYPE_2__ jv_object () ; 
 TYPE_2__ jv_object_get (TYPE_2__,TYPE_2__) ; 
 TYPE_2__ jv_object_set (TYPE_2__,TYPE_2__,TYPE_2__) ; 
 TYPE_2__ jv_parse (char*) ; 
 TYPE_2__ jv_string (char*) ; 
 TYPE_2__ jv_string_fmt (char*,...) ; 
 scalar_t__ jv_string_hash (TYPE_2__) ; 
 int jv_string_length_bytes (TYPE_2__) ; 
 TYPE_2__ jv_string_sized (char*,int) ; 
 char* jv_string_value (TYPE_2__) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void jv_test() {
  /// JSON parser regression tests
  {
    jv v = jv_parse("{\"a':\"12\"}");
    assert(jv_get_kind(v) == JV_KIND_INVALID);
    v = jv_invalid_get_msg(v);
    assert(strcmp(jv_string_value(v), "Expected separator between values at line 1, column 9 (while parsing '{\"a':\"12\"}')") == 0);
    jv_free(v);
  }
  /// Arrays and numbers
  {
    jv a = jv_array();
    assert(jv_get_kind(a) == JV_KIND_ARRAY);
    assert(jv_array_length(jv_copy(a)) == 0);
    assert(jv_array_length(jv_copy(a)) == 0);

    a = jv_array_append(a, jv_number(42));
    assert(jv_array_length(jv_copy(a)) == 1);
    assert(jv_number_value(jv_array_get(jv_copy(a), 0)) == 42);

    jv a2 = jv_array_append(jv_array(), jv_number(42));
    assert(jv_equal(jv_copy(a), jv_copy(a)));
    assert(jv_equal(jv_copy(a2), jv_copy(a2)));
    assert(jv_equal(jv_copy(a), jv_copy(a2)));
    assert(jv_equal(jv_copy(a2), jv_copy(a)));
    jv_free(a2);

    a2 = jv_array_append(jv_array(), jv_number(19));
    assert(!jv_equal(jv_copy(a), jv_copy(a2)));
    assert(!jv_equal(jv_copy(a2), jv_copy(a)));
    jv_free(a2);


    assert(jv_get_refcnt(a) == 1);
    a = jv_array_append(a, jv_copy(a));
    assert(jv_get_refcnt(a) == 1);

    assert(jv_array_length(jv_copy(a)) == 2);
    assert(jv_number_value(jv_array_get(jv_copy(a), 0)) == 42);

    for (int i=0; i<10; i++) {
      jv subarray = jv_array_get(jv_copy(a), 1);
      assert(jv_get_kind(subarray) == JV_KIND_ARRAY);
      assert(jv_array_length(jv_copy(subarray)) == 1);
      assert(jv_number_value(jv_array_get(jv_copy(subarray), 0)) == 42);
      jv_free(subarray);
    }


    jv subarray = jv_array_get(jv_copy(a), 1);
    assert(jv_get_kind(subarray) == JV_KIND_ARRAY);
    assert(jv_array_length(jv_copy(subarray)) == 1);
    assert(jv_number_value(jv_array_get(jv_copy(subarray), 0)) == 42);

    jv sub2 = jv_copy(subarray);
    sub2 = jv_array_append(sub2, jv_number(19));

    assert(jv_get_kind(sub2) == JV_KIND_ARRAY);
    assert(jv_array_length(jv_copy(sub2)) == 2);
    assert(jv_number_value(jv_array_get(jv_copy(sub2), 0)) == 42);
    assert(jv_number_value(jv_array_get(jv_copy(sub2), 1)) == 19);

    assert(jv_get_kind(subarray) == JV_KIND_ARRAY);
    assert(jv_array_length(jv_copy(subarray)) == 1);
    assert(jv_number_value(jv_array_get(jv_copy(subarray), 0)) == 42);

    jv_free(subarray);

    void* before = sub2.u.ptr;
    sub2 = jv_array_append(sub2, jv_number(200));
    void* after = sub2.u.ptr;
    assert(before == after);
    jv_free(sub2);

    jv a3 = jv_array_append(jv_copy(a), jv_number(19));
    assert(jv_array_length(jv_copy(a3)) == 3);
    assert(jv_number_value(jv_array_get(jv_copy(a3), 0)) == 42);
    assert(jv_array_length(jv_array_get(jv_copy(a3), 1)) == 1);
    assert(jv_number_value(jv_array_get(jv_copy(a3), 2)) == 19);
    jv_free(a3);


    jv a4 = jv_array();
    a4 = jv_array_append(a4, jv_number(1));
    a4 = jv_array_append(a4, jv_number(2));
    jv a5 = jv_copy(a4);
    a4 = jv_array_append(a4, jv_number(3));
    a4 = jv_array_slice(a4, 0, 1);
    assert(jv_array_length(jv_copy(a4)) == 1);
    a4 = jv_array_append(a4, jv_number(4));
    assert(jv_array_length(jv_copy(a4)) == 2);
    assert(jv_array_length(jv_copy(a5)) == 2);
    jv_free(a4);
    jv_free(a5);


    assert(jv_array_length(jv_copy(a)) == 2);
    assert(jv_number_value(jv_array_get(jv_copy(a), 0)) == 42);
    assert(jv_array_length(jv_array_get(jv_copy(a), 1)) == 1);


    //jv_dump(jv_copy(a), 0); printf("\n");
    jv_free(a);
  }


  /// Strings
  {
    assert(jv_equal(jv_string("foo"), jv_string_sized("foo", 3)));
    char nasty[] = "foo\0";
    jv shortstr = jv_string(nasty), longstr = jv_string_sized(nasty, sizeof(nasty));
    assert(jv_string_length_bytes(jv_copy(shortstr)) == (int)strlen(nasty));
    assert(jv_string_length_bytes(jv_copy(longstr)) == (int)sizeof(nasty));
    jv_free(shortstr);
    jv_free(longstr);


    char a1s[] = "hello", a2s[] = "hello", bs[] = "goodbye";
    jv a1 = jv_string(a1s), a2 = jv_string(a2s), b = jv_string(bs);
    assert(jv_equal(jv_copy(a1), jv_copy(a2)));
    assert(jv_equal(jv_copy(a2), jv_copy(a1)));
    assert(!jv_equal(jv_copy(a1), jv_copy(b)));

    assert(jv_string_hash(jv_copy(a1)) == jv_string_hash(jv_copy(a1)));
    assert(jv_string_hash(jv_copy(a1)) == jv_string_hash(jv_copy(a2)));
    assert(jv_string_hash(jv_copy(b)) != jv_string_hash(jv_copy(a1)));
    jv_free(a1);
    jv_free(a2);
    jv_free(b);

    assert(jv_equal(jv_string("hello42!"), jv_string_fmt("hello%d%s", 42, "!")));
    char big[20000];
    for (int i=0; i<(int)sizeof(big); i++) big[i] = 'a';
    big[sizeof(big)-1] = 0;
    jv str = jv_string_fmt("%s", big);
    assert(jv_string_length_bytes(jv_copy(str)) == sizeof(big) - 1);
    assert(!strcmp(big, jv_string_value(str)));
    jv_free(str);
  }

  /// Objects
  {
    jv o1 = jv_object();
    o1 = jv_object_set(o1, jv_string("foo"), jv_number(42));
    o1 = jv_object_set(o1, jv_string("bar"), jv_number(24));
    assert(jv_number_value(jv_object_get(jv_copy(o1), jv_string("foo"))) == 42);
    assert(jv_number_value(jv_object_get(jv_copy(o1), jv_string("bar"))) == 24);

    jv o2 = jv_object_set(jv_copy(o1), jv_string("foo"), jv_number(420));
    o2 = jv_object_set(o2, jv_string("bar"), jv_number(240));
    assert(jv_number_value(jv_object_get(jv_copy(o1), jv_string("foo"))) == 42);
    assert(jv_number_value(jv_object_get(jv_copy(o1), jv_string("bar"))) == 24);
    assert(jv_number_value(jv_object_get(jv_copy(o2), jv_string("foo"))) == 420);
    jv_free(o1);
    assert(jv_number_value(jv_object_get(jv_copy(o2), jv_string("bar"))) == 240);

    //jv_dump(jv_copy(o2), 0); printf("\n");
    jv_free(o2);
  }
}