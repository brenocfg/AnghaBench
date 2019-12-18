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
struct ber_element {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BER_CLASS_CONTEXT ; 
 unsigned long LDAP_FILT_AND ; 
 unsigned long LDAP_FILT_APPR ; 
 unsigned long LDAP_FILT_EQ ; 
 unsigned long LDAP_FILT_GE ; 
 unsigned long LDAP_FILT_LE ; 
 unsigned long LDAP_FILT_NOT ; 
 unsigned long LDAP_FILT_OR ; 
 unsigned long LDAP_FILT_PRES ; 
 unsigned long LDAP_FILT_SUBS ; 
 unsigned long LDAP_FILT_SUBS_ANY ; 
 unsigned long LDAP_FILT_SUBS_FIN ; 
 unsigned long LDAP_FILT_SUBS_INIT ; 
 struct ber_element* ber_add_nstring (struct ber_element*,char*,size_t) ; 
 struct ber_element* ber_add_sequence (struct ber_element*) ; 
 struct ber_element* ber_add_set (struct ber_element*) ; 
 int /*<<< orphan*/  ber_free_elements (struct ber_element*) ; 
 int /*<<< orphan*/  ber_link_elements (struct ber_element*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ber_set_header (struct ber_element*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* parseval (char*,size_t) ; 
 size_t strcspn (char*,char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static struct ber_element *
ldap_do_parse_search_filter(struct ber_element *prev, char **cpp)
{
	struct ber_element *elm, *root = NULL;
	char *attr_desc, *attr_val, *parsed_val, *cp;
	size_t len;
	unsigned long type;

	root = NULL;

	/* cpp should pass in pointer to opening parenthesis of "(filter)" */
	cp = *cpp;
	if (*cp != '(')
		goto syntaxfail;

	switch (*++cp) {
	case '&':		/* AND */
	case '|':		/* OR */
		if (*cp == '&')
			type = LDAP_FILT_AND;
		else
			type = LDAP_FILT_OR;

		if ((elm = ber_add_set(prev)) == NULL)
			goto callfail;
		root = elm;
		ber_set_header(elm, BER_CLASS_CONTEXT, type);

		if (*++cp != '(')		/* opening `(` of filter */
			goto syntaxfail;

		while (*cp == '(') {
			if ((elm =
			    ldap_do_parse_search_filter(elm, &cp)) == NULL)
				goto bad;
		}

		if (*cp != ')')			/* trailing `)` of filter */
			goto syntaxfail;
		break;

	case '!':		/* NOT */
		if ((root = ber_add_sequence(prev)) == NULL)
			goto callfail;
		ber_set_header(root, BER_CLASS_CONTEXT, LDAP_FILT_NOT);

		cp++;				/* now points to sub-filter */
		if ((elm = ldap_do_parse_search_filter(root, &cp)) == NULL)
			goto bad;

		if (*cp != ')')			/* trailing `)` of filter */
			goto syntaxfail;
		break;

	default:	/* SIMPLE || PRESENCE */
		attr_desc = cp;

		len = strcspn(cp, "()<>~=");
		cp += len;
		switch (*cp) {
		case '~':
			type = LDAP_FILT_APPR;
			cp++;
			break;
		case '<':
			type = LDAP_FILT_LE;
			cp++;
			break;
		case '>':
			type = LDAP_FILT_GE;
			cp++;
			break;
		case '=':
			type = LDAP_FILT_EQ;	/* assume EQ until disproven */
			break;
		case '(':
		case ')':
		default:
			goto syntaxfail;
		}
		attr_val = ++cp;

		/* presence filter */
		if (strncmp(attr_val, "*)", 2) == 0) {
			cp++;			/* point to trailing `)` */
			if ((root =
			    ber_add_nstring(prev, attr_desc, len)) == NULL)
				goto bad;

			ber_set_header(root, BER_CLASS_CONTEXT, LDAP_FILT_PRES);
			break;
		}

		if ((root = ber_add_sequence(prev)) == NULL)
			goto callfail;
		ber_set_header(root, BER_CLASS_CONTEXT, type);

		if ((elm = ber_add_nstring(root, attr_desc, len)) == NULL)
			goto callfail;

		len = strcspn(attr_val, "*)");
		if (len == 0 && *cp != '*')
			goto syntaxfail;
		cp += len;
		if (*cp == '\0')
			goto syntaxfail;

		if (*cp == '*') {	/* substring filter */
			int initial;

			cp = attr_val;

			ber_set_header(root, BER_CLASS_CONTEXT, LDAP_FILT_SUBS);

			if ((elm = ber_add_sequence(elm)) == NULL)
				goto callfail;

			for (initial = 1;; cp++, initial = 0) {
				attr_val = cp;

				len = strcspn(attr_val, "*)");
				if (len == 0) {
					if (*cp == ')')
						break;
					else
						continue;
				}
				cp += len;
				if (*cp == '\0')
					goto syntaxfail;

				if (initial)
					type = LDAP_FILT_SUBS_INIT;
				else if (*cp == ')')
					type = LDAP_FILT_SUBS_FIN;
				else
					type = LDAP_FILT_SUBS_ANY;

				if ((parsed_val = parseval(attr_val, len)) ==
				    NULL)
					goto callfail;
				elm = ber_add_nstring(elm, parsed_val,
				    strlen(parsed_val));
				free(parsed_val);
				if (elm == NULL)
					goto callfail;
				ber_set_header(elm, BER_CLASS_CONTEXT, type);
				if (type == LDAP_FILT_SUBS_FIN)
					break;
			}
			break;
		}

		if ((parsed_val = parseval(attr_val, len)) == NULL)
			goto callfail;
		elm = ber_add_nstring(elm, parsed_val, strlen(parsed_val));
		free(parsed_val);
		if (elm == NULL)
			goto callfail;
		break;
	}

	cp++;		/* now points one char beyond the trailing `)` */

	*cpp = cp;
	return (root);

syntaxfail:		/* XXX -- error reporting */
callfail:
bad:
	if (root != NULL)
		ber_free_elements(root);
	ber_link_elements(prev, NULL);
	return (NULL);
}