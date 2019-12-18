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
typedef  int uint8_t ;
typedef  uintptr_t uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int dtrace_json_state_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
#define  DTRACE_JSON_COLLECT_OBJECT 140 
#define  DTRACE_JSON_COLON 139 
#define  DTRACE_JSON_COMMA 138 
#define  DTRACE_JSON_IDENTIFIER 137 
#define  DTRACE_JSON_NUMBER 136 
#define  DTRACE_JSON_NUMBER_EXP 135 
#define  DTRACE_JSON_NUMBER_FRAC 134 
#define  DTRACE_JSON_OBJECT 133 
#define  DTRACE_JSON_REST 132 
#define  DTRACE_JSON_STRING 131 
#define  DTRACE_JSON_STRING_ESCAPE 130 
#define  DTRACE_JSON_STRING_ESCAPE_UNICODE 129 
#define  DTRACE_JSON_VALUE 128 
 int /*<<< orphan*/  INT64_MIN ; 
 char dtrace_load8 (uintptr_t) ; 
 int /*<<< orphan*/  dtrace_strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  dtrace_strtoll (char*,int,uintptr_t) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 int /*<<< orphan*/  islower (char) ; 
 int /*<<< orphan*/  isspace (char) ; 
 int /*<<< orphan*/  isxdigit (char) ; 

__attribute__((used)) static char *
dtrace_json(uint64_t size, uintptr_t json, char *elemlist, int nelems,
    char *dest)
{
	dtrace_json_state_t state = DTRACE_JSON_REST;
	int64_t array_elem = INT64_MIN;
	int64_t array_pos = 0;
	uint8_t escape_unicount = 0;
	boolean_t string_is_key = B_FALSE;
	boolean_t collect_object = B_FALSE;
	boolean_t found_key = B_FALSE;
	boolean_t in_array = B_FALSE;
	uint32_t braces = 0, brackets = 0;
	char *elem = elemlist;
	char *dd = dest;
	uintptr_t cur;

	for (cur = json; cur < json + size; cur++) {
		char cc = dtrace_load8(cur);
		if (cc == '\0')
			return (NULL);

		switch (state) {
		case DTRACE_JSON_REST:
			if (isspace(cc))
				break;

			if (cc == '{') {
				state = DTRACE_JSON_OBJECT;
				break;
			}

			if (cc == '[') {
				in_array = B_TRUE;
				array_pos = 0;
				array_elem = dtrace_strtoll(elem, 10, size);
				found_key = array_elem == 0 ? B_TRUE : B_FALSE;
				state = DTRACE_JSON_VALUE;
				break;
			}

			/*
			 * ERROR: expected to find a top-level object or array.
			 */
			return (NULL);
		case DTRACE_JSON_OBJECT:
			if (isspace(cc))
				break;

			if (cc == '"') {
				state = DTRACE_JSON_STRING;
				string_is_key = B_TRUE;
				break;
			}

			/*
			 * ERROR: either the object did not start with a key
			 * string, or we've run off the end of the object
			 * without finding the requested key.
			 */
			return (NULL);
		case DTRACE_JSON_STRING:
			if (cc == '\\') {
				*dd++ = '\\';
				state = DTRACE_JSON_STRING_ESCAPE;
				break;
			}

			if (cc == '"') {
				if (collect_object) {
					/*
					 * We don't reset the dest here, as
					 * the string is part of a larger
					 * object being collected.
					 */
					*dd++ = cc;
					collect_object = B_FALSE;
					state = DTRACE_JSON_COLLECT_OBJECT;
					break;
				}
				*dd = '\0';
				dd = dest; /* reset string buffer */
				if (string_is_key) {
					if (dtrace_strncmp(dest, elem,
					    size) == 0)
						found_key = B_TRUE;
				} else if (found_key) {
					if (nelems > 1) {
						/*
						 * We expected an object, not
						 * this string.
						 */
						return (NULL);
					}
					return (dest);
				}
				state = string_is_key ? DTRACE_JSON_COLON :
				    DTRACE_JSON_COMMA;
				string_is_key = B_FALSE;
				break;
			}

			*dd++ = cc;
			break;
		case DTRACE_JSON_STRING_ESCAPE:
			*dd++ = cc;
			if (cc == 'u') {
				escape_unicount = 0;
				state = DTRACE_JSON_STRING_ESCAPE_UNICODE;
			} else {
				state = DTRACE_JSON_STRING;
			}
			break;
		case DTRACE_JSON_STRING_ESCAPE_UNICODE:
			if (!isxdigit(cc)) {
				/*
				 * ERROR: invalid unicode escape, expected
				 * four valid hexidecimal digits.
				 */
				return (NULL);
			}

			*dd++ = cc;
			if (++escape_unicount == 4)
				state = DTRACE_JSON_STRING;
			break;
		case DTRACE_JSON_COLON:
			if (isspace(cc))
				break;

			if (cc == ':') {
				state = DTRACE_JSON_VALUE;
				break;
			}

			/*
			 * ERROR: expected a colon.
			 */
			return (NULL);
		case DTRACE_JSON_COMMA:
			if (isspace(cc))
				break;

			if (cc == ',') {
				if (in_array) {
					state = DTRACE_JSON_VALUE;
					if (++array_pos == array_elem)
						found_key = B_TRUE;
				} else {
					state = DTRACE_JSON_OBJECT;
				}
				break;
			}

			/*
			 * ERROR: either we hit an unexpected character, or
			 * we reached the end of the object or array without
			 * finding the requested key.
			 */
			return (NULL);
		case DTRACE_JSON_IDENTIFIER:
			if (islower(cc)) {
				*dd++ = cc;
				break;
			}

			*dd = '\0';
			dd = dest; /* reset string buffer */

			if (dtrace_strncmp(dest, "true", 5) == 0 ||
			    dtrace_strncmp(dest, "false", 6) == 0 ||
			    dtrace_strncmp(dest, "null", 5) == 0) {
				if (found_key) {
					if (nelems > 1) {
						/*
						 * ERROR: We expected an object,
						 * not this identifier.
						 */
						return (NULL);
					}
					return (dest);
				} else {
					cur--;
					state = DTRACE_JSON_COMMA;
					break;
				}
			}

			/*
			 * ERROR: we did not recognise the identifier as one
			 * of those in the JSON specification.
			 */
			return (NULL);
		case DTRACE_JSON_NUMBER:
			if (cc == '.') {
				*dd++ = cc;
				state = DTRACE_JSON_NUMBER_FRAC;
				break;
			}

			if (cc == 'x' || cc == 'X') {
				/*
				 * ERROR: specification explicitly excludes
				 * hexidecimal or octal numbers.
				 */
				return (NULL);
			}

			/* FALLTHRU */
		case DTRACE_JSON_NUMBER_FRAC:
			if (cc == 'e' || cc == 'E') {
				*dd++ = cc;
				state = DTRACE_JSON_NUMBER_EXP;
				break;
			}

			if (cc == '+' || cc == '-') {
				/*
				 * ERROR: expect sign as part of exponent only.
				 */
				return (NULL);
			}
			/* FALLTHRU */
		case DTRACE_JSON_NUMBER_EXP:
			if (isdigit(cc) || cc == '+' || cc == '-') {
				*dd++ = cc;
				break;
			}

			*dd = '\0';
			dd = dest; /* reset string buffer */
			if (found_key) {
				if (nelems > 1) {
					/*
					 * ERROR: We expected an object, not
					 * this number.
					 */
					return (NULL);
				}
				return (dest);
			}

			cur--;
			state = DTRACE_JSON_COMMA;
			break;
		case DTRACE_JSON_VALUE:
			if (isspace(cc))
				break;

			if (cc == '{' || cc == '[') {
				if (nelems > 1 && found_key) {
					in_array = cc == '[' ? B_TRUE : B_FALSE;
					/*
					 * If our element selector directs us
					 * to descend into this nested object,
					 * then move to the next selector
					 * element in the list and restart the
					 * state machine.
					 */
					while (*elem != '\0')
						elem++;
					elem++; /* skip the inter-element NUL */
					nelems--;
					dd = dest;
					if (in_array) {
						state = DTRACE_JSON_VALUE;
						array_pos = 0;
						array_elem = dtrace_strtoll(
						    elem, 10, size);
						found_key = array_elem == 0 ?
						    B_TRUE : B_FALSE;
					} else {
						found_key = B_FALSE;
						state = DTRACE_JSON_OBJECT;
					}
					break;
				}

				/*
				 * Otherwise, we wish to either skip this
				 * nested object or return it in full.
				 */
				if (cc == '[')
					brackets = 1;
				else
					braces = 1;
				*dd++ = cc;
				state = DTRACE_JSON_COLLECT_OBJECT;
				break;
			}

			if (cc == '"') {
				state = DTRACE_JSON_STRING;
				break;
			}

			if (islower(cc)) {
				/*
				 * Here we deal with true, false and null.
				 */
				*dd++ = cc;
				state = DTRACE_JSON_IDENTIFIER;
				break;
			}

			if (cc == '-' || isdigit(cc)) {
				*dd++ = cc;
				state = DTRACE_JSON_NUMBER;
				break;
			}

			/*
			 * ERROR: unexpected character at start of value.
			 */
			return (NULL);
		case DTRACE_JSON_COLLECT_OBJECT:
			if (cc == '\0')
				/*
				 * ERROR: unexpected end of input.
				 */
				return (NULL);

			*dd++ = cc;
			if (cc == '"') {
				collect_object = B_TRUE;
				state = DTRACE_JSON_STRING;
				break;
			}

			if (cc == ']') {
				if (brackets-- == 0) {
					/*
					 * ERROR: unbalanced brackets.
					 */
					return (NULL);
				}
			} else if (cc == '}') {
				if (braces-- == 0) {
					/*
					 * ERROR: unbalanced braces.
					 */
					return (NULL);
				}
			} else if (cc == '{') {
				braces++;
			} else if (cc == '[') {
				brackets++;
			}

			if (brackets == 0 && braces == 0) {
				if (found_key) {
					*dd = '\0';
					return (dest);
				}
				dd = dest; /* reset string buffer */
				state = DTRACE_JSON_COMMA;
			}
			break;
		}
	}
	return (NULL);
}