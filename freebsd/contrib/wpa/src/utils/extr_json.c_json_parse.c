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
struct json_token {void* state; char* string; char* name; int number; void* type; struct json_token* parent; struct json_token* sibling; struct json_token* child; } ;

/* Variables and functions */
 void* JSON_ARRAY ; 
 void* JSON_BOOLEAN ; 
 void* JSON_COMPLETED ; 
 void* JSON_EMPTY ; 
 unsigned int JSON_MAX_DEPTH ; 
 void* JSON_NULL ; 
 void* JSON_NUMBER ; 
 void* JSON_OBJECT ; 
 void* JSON_STARTED ; 
 void* JSON_STRING ; 
 void* JSON_VALUE ; 
 void* JSON_WAITING_VALUE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 void* json_alloc_token (unsigned int*) ; 
 scalar_t__ json_check_tree_state (struct json_token*) ; 
 int /*<<< orphan*/  json_free (struct json_token*) ; 
 int /*<<< orphan*/  json_parse_number (char const**,char const*,int*) ; 
 char* json_parse_string (char const**,char const*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int /*<<< orphan*/  os_strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

struct json_token * json_parse(const char *data, size_t data_len)
{
	struct json_token *root = NULL, *curr_token = NULL, *token = NULL;
	const char *pos, *end;
	char *str;
	int num;
	unsigned int depth = 0;
	unsigned int tokens = 0;

	pos = data;
	end = data + data_len;

	for (; pos < end; pos++) {
		switch (*pos) {
		case '[': /* start array */
		case '{': /* start object */
			if (!curr_token) {
				token = json_alloc_token(&tokens);
				if (!token)
					goto fail;
				if (!root)
					root = token;
			} else if (curr_token->state == JSON_WAITING_VALUE) {
				token = curr_token;
			} else if (curr_token->parent &&
				   curr_token->parent->type == JSON_ARRAY &&
				   curr_token->parent->state == JSON_STARTED &&
				   curr_token->state == JSON_EMPTY) {
				token = curr_token;
			} else {
				wpa_printf(MSG_DEBUG,
					   "JSON: Invalid state for start array/object");
				goto fail;
			}
			depth++;
			if (depth > JSON_MAX_DEPTH) {
				wpa_printf(MSG_DEBUG,
					   "JSON: Max depth exceeded");
				goto fail;
			}
			token->type = *pos == '[' ? JSON_ARRAY : JSON_OBJECT;
			token->state = JSON_STARTED;
			token->child = json_alloc_token(&tokens);
			if (!token->child)
				goto fail;
			curr_token = token->child;
			curr_token->parent = token;
			curr_token->state = JSON_EMPTY;
			break;
		case ']': /* end array */
		case '}': /* end object */
			if (!curr_token || !curr_token->parent ||
			    curr_token->parent->state != JSON_STARTED) {
				wpa_printf(MSG_DEBUG,
					   "JSON: Invalid state for end array/object");
				goto fail;
			}
			depth--;
			curr_token = curr_token->parent;
			if ((*pos == ']' &&
			     curr_token->type != JSON_ARRAY) ||
			    (*pos == '}' &&
			     curr_token->type != JSON_OBJECT)) {
				wpa_printf(MSG_DEBUG,
					   "JSON: Array/Object mismatch");
				goto fail;
			}
			if (curr_token->child->state == JSON_EMPTY &&
			    !curr_token->child->child &&
			    !curr_token->child->sibling) {
				/* Remove pending child token since the
				 * array/object was empty. */
				json_free(curr_token->child);
				curr_token->child = NULL;
			}
			curr_token->state = JSON_COMPLETED;
			break;
		case '\"': /* string */
			str = json_parse_string(&pos, end);
			if (!str)
				goto fail;
			if (!curr_token) {
				token = json_alloc_token(&tokens);
				if (!token)
					goto fail;
				token->type = JSON_STRING;
				token->string = str;
				token->state = JSON_COMPLETED;
			} else if (curr_token->parent &&
				   curr_token->parent->type == JSON_ARRAY &&
				   curr_token->parent->state == JSON_STARTED &&
				   curr_token->state == JSON_EMPTY) {
				curr_token->string = str;
				curr_token->state = JSON_COMPLETED;
				curr_token->type = JSON_STRING;
				wpa_printf(MSG_MSGDUMP,
					   "JSON: String value: '%s'",
					   curr_token->string);
			} else if (curr_token->state == JSON_EMPTY) {
				curr_token->type = JSON_VALUE;
				curr_token->name = str;
				curr_token->state = JSON_STARTED;
			} else if (curr_token->state == JSON_WAITING_VALUE) {
				curr_token->string = str;
				curr_token->state = JSON_COMPLETED;
				curr_token->type = JSON_STRING;
				wpa_printf(MSG_MSGDUMP,
					   "JSON: String value: '%s' = '%s'",
					   curr_token->name,
					   curr_token->string);
			} else {
				wpa_printf(MSG_DEBUG,
					   "JSON: Invalid state for a string");
				os_free(str);
				goto fail;
			}
			break;
		case ' ':
		case '\t':
		case '\r':
		case '\n':
			/* ignore whitespace */
			break;
		case ':': /* name/value separator */
			if (!curr_token || curr_token->state != JSON_STARTED)
				goto fail;
			curr_token->state = JSON_WAITING_VALUE;
			break;
		case ',': /* member separator */
			if (!curr_token)
				goto fail;
			curr_token->sibling = json_alloc_token(&tokens);
			if (!curr_token->sibling)
				goto fail;
			curr_token->sibling->parent = curr_token->parent;
			curr_token = curr_token->sibling;
			curr_token->state = JSON_EMPTY;
			break;
		case 't': /* true */
		case 'f': /* false */
		case 'n': /* null */
			if (!((end - pos >= 4 &&
			       os_strncmp(pos, "true", 4) == 0) ||
			      (end - pos >= 5 &&
			       os_strncmp(pos, "false", 5) == 0) ||
			      (end - pos >= 4 &&
			       os_strncmp(pos, "null", 4) == 0))) {
				wpa_printf(MSG_DEBUG,
					   "JSON: Invalid literal name");
				goto fail;
			}
			if (!curr_token) {
				token = json_alloc_token(&tokens);
				if (!token)
					goto fail;
				curr_token = token;
			} else if (curr_token->state == JSON_WAITING_VALUE) {
				wpa_printf(MSG_MSGDUMP,
					   "JSON: Literal name: '%s' = %c",
					   curr_token->name, *pos);
			} else if (curr_token->parent &&
				   curr_token->parent->type == JSON_ARRAY &&
				   curr_token->parent->state == JSON_STARTED &&
				   curr_token->state == JSON_EMPTY) {
				wpa_printf(MSG_MSGDUMP,
					   "JSON: Literal name: %c", *pos);
			} else {
				wpa_printf(MSG_DEBUG,
					   "JSON: Invalid state for a literal name");
				goto fail;
			}
			switch (*pos) {
			case 't':
				curr_token->type = JSON_BOOLEAN;
				curr_token->number = 1;
				pos += 3;
				break;
			case 'f':
				curr_token->type = JSON_BOOLEAN;
				curr_token->number = 0;
				pos += 4;
				break;
			case 'n':
				curr_token->type = JSON_NULL;
				pos += 3;
				break;
			}
			curr_token->state = JSON_COMPLETED;
			break;
		case '-':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			/* number */
			if (json_parse_number(&pos, end, &num) < 0)
				goto fail;
			if (!curr_token) {
				token = json_alloc_token(&tokens);
				if (!token)
					goto fail;
				token->type = JSON_NUMBER;
				token->number = num;
				token->state = JSON_COMPLETED;
			} else if (curr_token->state == JSON_WAITING_VALUE) {
				curr_token->number = num;
				curr_token->state = JSON_COMPLETED;
				curr_token->type = JSON_NUMBER;
				wpa_printf(MSG_MSGDUMP,
					   "JSON: Number value: '%s' = '%d'",
					   curr_token->name,
					   curr_token->number);
			} else if (curr_token->parent &&
				   curr_token->parent->type == JSON_ARRAY &&
				   curr_token->parent->state == JSON_STARTED &&
				   curr_token->state == JSON_EMPTY) {
				curr_token->number = num;
				curr_token->state = JSON_COMPLETED;
				curr_token->type = JSON_NUMBER;
				wpa_printf(MSG_MSGDUMP,
					   "JSON: Number value: %d",
					   curr_token->number);
			} else {
				wpa_printf(MSG_DEBUG,
					   "JSON: Invalid state for a number");
				goto fail;
			}
			break;
		default:
			wpa_printf(MSG_DEBUG,
				   "JSON: Unexpected JSON character: %c", *pos);
			goto fail;
		}

		if (!root)
			root = token;
		if (!curr_token)
			curr_token = token;
	}

	if (json_check_tree_state(root) < 0) {
		wpa_printf(MSG_DEBUG, "JSON: Incomplete token in the tree");
		goto fail;
	}

	return root;
fail:
	wpa_printf(MSG_DEBUG, "JSON: Parsing failed");
	json_free(root);
	return NULL;
}