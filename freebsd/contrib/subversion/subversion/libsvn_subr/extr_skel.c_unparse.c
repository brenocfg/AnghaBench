#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ len; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
struct TYPE_11__ {char* data; scalar_t__ len; struct TYPE_11__* next; struct TYPE_11__* children; scalar_t__ is_atom; } ;
typedef  TYPE_2__ svn_skel_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT_NO_RETURN (int) ; 
 int /*<<< orphan*/  SVN_INT64_BUFFER_SIZE ; 
 scalar_t__ svn__ui64toa (char*,scalar_t__) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbyte (TYPE_1__*,char) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbytes (TYPE_1__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  svn_stringbuf_ensure (TYPE_1__*,scalar_t__) ; 
 scalar_t__ use_implicit (TYPE_2__ const*) ; 

__attribute__((used)) static svn_stringbuf_t *
unparse(const svn_skel_t *skel, svn_stringbuf_t *str)
{
  if (skel->is_atom)
    {
      /* Append an atom to STR.  */
      if (use_implicit(skel))
        svn_stringbuf_appendbytes(str, skel->data, skel->len);
      else
        {
          /* Append the length to STR.  Ensure enough space for at least
           * one 64 bit int. */
          char buf[200 + SVN_INT64_BUFFER_SIZE];
          apr_size_t length_len;

          length_len = svn__ui64toa(buf, skel->len);

          SVN_ERR_ASSERT_NO_RETURN(length_len > 0);

          /* Make sure we have room for the length, the space, and the
             atom's contents.  */
          svn_stringbuf_ensure(str, str->len + length_len + 1 + skel->len);
          svn_stringbuf_appendbytes(str, buf, length_len);
          svn_stringbuf_appendbyte(str, ' ');
          svn_stringbuf_appendbytes(str, skel->data, skel->len);
        }
    }
  else
    {
      /* Append a list to STR: an opening parenthesis, the list elements
       * separated by a space, and a closing parenthesis.  */
      svn_skel_t *child;

      svn_stringbuf_appendbyte(str, '(');

      for (child = skel->children; child; child = child->next)
        {
          unparse(child, str);
          if (child->next)
            svn_stringbuf_appendbyte(str, ' ');
        }

      svn_stringbuf_appendbyte(str, ')');
    }

  return str;
}