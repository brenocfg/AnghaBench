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
struct TYPE_5__ {char* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 char* svn_hash_gets (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_stringbuf_appendcstr (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  svn_stringbuf_chop (TYPE_1__*,int) ; 
 TYPE_1__* svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
convert_organisation_to_str(apr_hash_t *org, apr_pool_t *pool)
{
  const char *cn = svn_hash_gets(org, "CN");
  const char *org_unit = svn_hash_gets(org, "OU");
  const char *org_name = svn_hash_gets(org, "O");
  const char *locality = svn_hash_gets(org, "L");
  const char *state = svn_hash_gets(org, "ST");
  const char *country = svn_hash_gets(org, "C");
  const char *email = svn_hash_gets(org, "E");
  svn_stringbuf_t *buf = svn_stringbuf_create_empty(pool);

  if (cn)
    {
      svn_stringbuf_appendcstr(buf, cn);
      svn_stringbuf_appendcstr(buf, ", ");
    }

  if (org_unit)
    {
      svn_stringbuf_appendcstr(buf, org_unit);
      svn_stringbuf_appendcstr(buf, ", ");
    }

  if (org_name)
    {
      svn_stringbuf_appendcstr(buf, org_name);
      svn_stringbuf_appendcstr(buf, ", ");
    }

  if (locality)
    {
      svn_stringbuf_appendcstr(buf, locality);
      svn_stringbuf_appendcstr(buf, ", ");
    }

  if (state)
    {
      svn_stringbuf_appendcstr(buf, state);
      svn_stringbuf_appendcstr(buf, ", ");
    }

  if (country)
    {
      svn_stringbuf_appendcstr(buf, country);
      svn_stringbuf_appendcstr(buf, ", ");
    }

  /* Chop ', ' if any. */
  svn_stringbuf_chop(buf, 2);

  if (email)
    {
      svn_stringbuf_appendcstr(buf, "(");
      svn_stringbuf_appendcstr(buf, email);
      svn_stringbuf_appendcstr(buf, ")");
    }

  return buf->data;
}