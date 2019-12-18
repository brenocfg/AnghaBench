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
struct type {int dummy; } ;
struct objfile {int dummy; } ;
struct field {struct type* type; } ;

/* Variables and functions */
 int /*<<< orphan*/  STABS_CONTINUE (char**,struct objfile*) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_VOID ; 
 int /*<<< orphan*/  memset (struct field*,int /*<<< orphan*/ ,int) ; 
 struct type* read_type (char**,struct objfile*) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static struct field *
read_args (char **pp, int end, struct objfile *objfile, int *nargsp,
	   int *varargsp)
{
  /* FIXME!  Remove this arbitrary limit!  */
  struct type *types[1024];	/* allow for fns of 1023 parameters */
  int n = 0, i;
  struct field *rval;

  while (**pp != end)
    {
      if (**pp != ',')
	/* Invalid argument list: no ','.  */
	return (struct field *) -1;
      (*pp)++;
      STABS_CONTINUE (pp, objfile);
      types[n++] = read_type (pp, objfile);
    }
  (*pp)++;			/* get past `end' (the ':' character) */

  if (TYPE_CODE (types[n - 1]) != TYPE_CODE_VOID)
    *varargsp = 1;
  else
    {
      n--;
      *varargsp = 0;
    }

  rval = (struct field *) xmalloc (n * sizeof (struct field));
  memset (rval, 0, n * sizeof (struct field));
  for (i = 0; i < n; i++)
    rval[i].type = types[i];
  *nargsp = n;
  return rval;
}