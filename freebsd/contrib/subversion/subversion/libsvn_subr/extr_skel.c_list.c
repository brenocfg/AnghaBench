#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* data; int len; struct TYPE_5__* children; int /*<<< orphan*/  is_atom; struct TYPE_5__* next; } ;
typedef  TYPE_1__ svn_skel_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* parse (char const*,int,int /*<<< orphan*/ *) ; 
 scalar_t__* skel_char_type ; 
 scalar_t__ type_space ; 

__attribute__((used)) static svn_skel_t *
list(const char *data,
     apr_size_t len,
     apr_pool_t *pool)
{
  const char *end = data + len;
  const char *list_start;

  /* Verify that the list starts with an opening paren.  At the
     moment, all callers have checked this already, but it's more
     robust this way.  */
  if (data >= end || *data != '(')
    return NULL;

  /* Mark where the list starts.  */
  list_start = data;

  /* Skip the opening paren.  */
  data++;

  /* Parse the children.  */
  {
    svn_skel_t *children = NULL;
    svn_skel_t **tail = &children;

    for (;;)
      {
        svn_skel_t *element;

        /* Skip any whitespace.  */
        while (data < end
               && skel_char_type[(unsigned char) *data] == type_space)
          data++;

        /* End of data, but no closing paren?  */
        if (data >= end)
          return NULL;

        /* End of list?  */
        if (*data == ')')
          {
            data++;
            break;
          }

        /* Parse the next element in the list.  */
        element = parse(data, end - data, pool);
        if (! element)
          return NULL;

        /* Link that element into our list.  */
        element->next = NULL;
        *tail = element;
        tail = &element->next;

        /* Advance past that element.  */
        data = element->data + element->len;
      }

    /* Construct the return value.  */
    {
      svn_skel_t *s = apr_pcalloc(pool, sizeof(*s));

      s->is_atom = FALSE;
      s->data = list_start;
      s->len = data - list_start;
      s->children = children;

      return s;
    }
  }
}