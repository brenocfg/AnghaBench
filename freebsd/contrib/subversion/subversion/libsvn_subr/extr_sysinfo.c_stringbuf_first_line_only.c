#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int data; char* len; } ;
typedef  TYPE_1__ svn_stringbuf_t ;

/* Variables and functions */
 char* strchr (int,char) ; 
 int /*<<< orphan*/  svn_stringbuf_strip_whitespace (TYPE_1__*) ; 

__attribute__((used)) static void
stringbuf_first_line_only(svn_stringbuf_t *buffer)
{
  char *eol = strchr(buffer->data, '\n');
  if (eol)
    {
      *eol = '\0';
      buffer->len = 1 + eol - buffer->data;
    }
  svn_stringbuf_strip_whitespace(buffer);
}