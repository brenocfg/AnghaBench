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
struct TYPE_3__ {unsigned int type; char* tag_name; char* tagger; char* message; int /*<<< orphan*/  target; } ;
typedef  TYPE_1__ git_tag ;
typedef  int /*<<< orphan*/  git_signature ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (char*) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_ADD (size_t*,size_t,int) ; 
 unsigned int GIT_OBJECT_INVALID ; 
 void* git__malloc (size_t) ; 
 char* git__memmem (char const*,int,char*,int) ; 
 scalar_t__ git_oid__parse (int /*<<< orphan*/ *,char const**,char const*,char*) ; 
 scalar_t__ git_signature__parse (char*,char const**,char const*,char*,char) ; 
 char* memchr (char const*,char,int) ; 
 scalar_t__ memcmp (char const*,char const*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 
 int tag_error (char*) ; 

__attribute__((used)) static int tag_parse(git_tag *tag, const char *buffer, const char *buffer_end)
{
	static const char *tag_types[] = {
		NULL, "commit\n", "tree\n", "blob\n", "tag\n"
	};
	size_t text_len, alloc_len;
	const char *search;
	unsigned int i;

	if (git_oid__parse(&tag->target, &buffer, buffer_end, "object ") < 0)
		return tag_error("object field invalid");

	if (buffer + 5 >= buffer_end)
		return tag_error("object too short");

	if (memcmp(buffer, "type ", 5) != 0)
		return tag_error("type field not found");
	buffer += 5;

	tag->type = GIT_OBJECT_INVALID;

	for (i = 1; i < ARRAY_SIZE(tag_types); ++i) {
		size_t type_length = strlen(tag_types[i]);

		if (buffer + type_length >= buffer_end)
			return tag_error("object too short");

		if (memcmp(buffer, tag_types[i], type_length) == 0) {
			tag->type = i;
			buffer += type_length;
			break;
		}
	}

	if (tag->type == GIT_OBJECT_INVALID)
		return tag_error("invalid object type");

	if (buffer + 4 >= buffer_end)
		return tag_error("object too short");

	if (memcmp(buffer, "tag ", 4) != 0)
		return tag_error("tag field not found");

	buffer += 4;

	search = memchr(buffer, '\n', buffer_end - buffer);
	if (search == NULL)
		return tag_error("object too short");

	text_len = search - buffer;

	GIT_ERROR_CHECK_ALLOC_ADD(&alloc_len, text_len, 1);
	tag->tag_name = git__malloc(alloc_len);
	GIT_ERROR_CHECK_ALLOC(tag->tag_name);

	memcpy(tag->tag_name, buffer, text_len);
	tag->tag_name[text_len] = '\0';

	buffer = search + 1;

	tag->tagger = NULL;
	if (buffer < buffer_end && *buffer != '\n') {
		tag->tagger = git__malloc(sizeof(git_signature));
		GIT_ERROR_CHECK_ALLOC(tag->tagger);

		if (git_signature__parse(tag->tagger, &buffer, buffer_end, "tagger ", '\n') < 0)
			return -1;
	}

	tag->message = NULL;
	if (buffer < buffer_end) {
		/* If we're not at the end of the header, search for it */
		if(*buffer != '\n') {
			search = git__memmem(buffer, buffer_end - buffer,
					     "\n\n", 2);
			if (search)
				buffer = search + 1;
			else
				return tag_error("tag contains no message");
		}

		text_len = buffer_end - ++buffer;

		GIT_ERROR_CHECK_ALLOC_ADD(&alloc_len, text_len, 1);
		tag->message = git__malloc(alloc_len);
		GIT_ERROR_CHECK_ALLOC(tag->message);

		memcpy(tag->message, buffer, text_len);
		tag->message[text_len] = '\0';
	}

	return 0;
}