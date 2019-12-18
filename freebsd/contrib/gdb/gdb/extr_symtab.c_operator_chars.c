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

/* Variables and functions */
 int /*<<< orphan*/  error (char*,...) ; 
 scalar_t__ isalnum (char) ; 
 scalar_t__ isalpha (char) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

char *
operator_chars (char *p, char **end)
{
  *end = "";
  if (strncmp (p, "operator", 8))
    return *end;
  p += 8;

  /* Don't get faked out by `operator' being part of a longer
     identifier.  */
  if (isalpha (*p) || *p == '_' || *p == '$' || *p == '\0')
    return *end;

  /* Allow some whitespace between `operator' and the operator symbol.  */
  while (*p == ' ' || *p == '\t')
    p++;

  /* Recognize 'operator TYPENAME'. */

  if (isalpha (*p) || *p == '_' || *p == '$')
    {
      char *q = p + 1;
      while (isalnum (*q) || *q == '_' || *q == '$')
	q++;
      *end = q;
      return p;
    }

  while (*p)
    switch (*p)
      {
      case '\\':			/* regexp quoting */
	if (p[1] == '*')
	  {
	    if (p[2] == '=')	/* 'operator\*=' */
	      *end = p + 3;
	    else			/* 'operator\*'  */
	      *end = p + 2;
	    return p;
	  }
	else if (p[1] == '[')
	  {
	    if (p[2] == ']')
	      error ("mismatched quoting on brackets, try 'operator\\[\\]'");
	    else if (p[2] == '\\' && p[3] == ']')
	      {
		*end = p + 4;	/* 'operator\[\]' */
		return p;
	      }
	    else
	      error ("nothing is allowed between '[' and ']'");
	  }
	else 
	  {
	    /* Gratuitous qoute: skip it and move on. */
	    p++;
	    continue;
	  }
	break;
      case '!':
      case '=':
      case '*':
      case '/':
      case '%':
      case '^':
	if (p[1] == '=')
	  *end = p + 2;
	else
	  *end = p + 1;
	return p;
      case '<':
      case '>':
      case '+':
      case '-':
      case '&':
      case '|':
	if (p[0] == '-' && p[1] == '>')
	  {
	    /* Struct pointer member operator 'operator->'. */
	    if (p[2] == '*')
	      {
		*end = p + 3;	/* 'operator->*' */
		return p;
	      }
	    else if (p[2] == '\\')
	      {
		*end = p + 4;	/* Hopefully 'operator->\*' */
		return p;
	      }
	    else
	      {
		*end = p + 2;	/* 'operator->' */
		return p;
	      }
	  }
	if (p[1] == '=' || p[1] == p[0])
	  *end = p + 2;
	else
	  *end = p + 1;
	return p;
      case '~':
      case ',':
	*end = p + 1;
	return p;
      case '(':
	if (p[1] != ')')
	  error ("`operator ()' must be specified without whitespace in `()'");
	*end = p + 2;
	return p;
      case '?':
	if (p[1] != ':')
	  error ("`operator ?:' must be specified without whitespace in `?:'");
	*end = p + 2;
	return p;
      case '[':
	if (p[1] != ']')
	  error ("`operator []' must be specified without whitespace in `[]'");
	*end = p + 2;
	return p;
      default:
	error ("`operator %s' not supported", p);
	break;
      }

  *end = "";
  return *end;
}