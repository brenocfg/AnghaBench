#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * route; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ MatcherEntry ;
typedef  int /*<<< orphan*/  Matcher ;
typedef  int /*<<< orphan*/  MatchDictEntry ;

/* Variables and functions */
 int /*<<< orphan*/ * MatchDict_entries_to_dict (int /*<<< orphan*/ *,size_t) ; 
 TYPE_1__* Matcher_match_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/ * PyTuple_New (int) ; 
 int /*<<< orphan*/  PyTuple_SET_ITEM (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject*
_Matcher_match_request(Matcher* self, PyObject* request)
{
  MatcherEntry* matcher_entry;
  MatchDictEntry* entries;
  PyObject* route = NULL;
  size_t length;
  PyObject* match_dict = NULL;
  PyObject* route_dict = NULL;

  if(!(matcher_entry = Matcher_match_request(
       self, request, &entries, &length)))
    Py_RETURN_NONE;

  route = matcher_entry->route;

  if(!(match_dict = MatchDict_entries_to_dict(entries, length)))
    goto error;

  if(!(route_dict = PyTuple_New(2)))
    goto error;

  PyTuple_SET_ITEM(route_dict, 0, route);
  PyTuple_SET_ITEM(route_dict, 1, match_dict);

  goto finally;

  error:
  Py_XDECREF(match_dict);
  route = NULL;

  finally:
  if(route)
    Py_INCREF(route);
  return route_dict;
}