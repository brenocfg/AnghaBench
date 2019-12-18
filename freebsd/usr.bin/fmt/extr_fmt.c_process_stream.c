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
typedef  char wchar_t ;
typedef  scalar_t__ HdrType ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t SILLY ; 
 int /*<<< orphan*/  allow_indented_paragraphs ; 
 scalar_t__ centerP ; 
 int /*<<< orphan*/  center_stream (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  format_troff ; 
 char* get_line (int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ grok_mail_headers ; 
 scalar_t__ hdr_Continuation ; 
 scalar_t__ hdr_Header ; 
 scalar_t__ hdr_NonHeader ; 
 scalar_t__ hdr_ParagraphStart ; 
 size_t indent_length (char*,size_t) ; 
 scalar_t__ might_be_header (char*) ; 
 int /*<<< orphan*/  n_errors ; 
 int /*<<< orphan*/  new_paragraph (size_t,size_t) ; 
 scalar_t__ output_in_paragraph ; 
 int /*<<< orphan*/  output_word (size_t,size_t,char*,size_t,size_t) ; 
 int /*<<< orphan*/  putwchar (char) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 
 int /*<<< orphan*/  wprintf (char*,int,char*) ; 

__attribute__((used)) static void
process_stream(FILE *stream, const char *name)
{
	size_t last_indent = SILLY;	/* how many spaces in last indent? */
	size_t para_line_number = 0;	/* how many lines already read in this para? */
	size_t first_indent = SILLY;	/* indentation of line 0 of paragraph */
	HdrType prev_header_type = hdr_ParagraphStart;

	/* ^-- header_type of previous line; -1 at para start */
	wchar_t *line;
	size_t length;

	if (centerP) {
		center_stream(stream, name);
		return;
	}
	while ((line = get_line(stream, &length)) != NULL) {
		size_t np = indent_length(line, length);

		{
			HdrType header_type = hdr_NonHeader;

			if (grok_mail_headers && prev_header_type != hdr_NonHeader) {
				if (np == 0 && might_be_header(line))
					header_type = hdr_Header;
				else if (np > 0 && prev_header_type > hdr_NonHeader)
					header_type = hdr_Continuation;
			}
			/*
			 * We need a new paragraph if and only if: this line
			 * is blank, OR it's a troff request (and we don't
			 * format troff), OR it's a mail header, OR it's not
			 * a mail header AND the last line was one, OR the
			 * indentation has changed AND the line isn't a mail
			 * header continuation line AND this isn't the
			 * second line of an indented paragraph.
			 */
			if (length == 0
			    || (line[0] == '.' && !format_troff)
			    || header_type == hdr_Header
			    || (header_type == hdr_NonHeader && prev_header_type > hdr_NonHeader)
			    || (np != last_indent
			    && header_type != hdr_Continuation
			    && (!allow_indented_paragraphs || para_line_number != 1))) {
				new_paragraph(output_in_paragraph ? last_indent : first_indent, np);
				para_line_number = 0;
				first_indent = np;
				last_indent = np;
				if (header_type == hdr_Header)
					last_indent = 2;	/* for cont. lines */
				if (length == 0 || (line[0] == '.' && !format_troff)) {
					if (length == 0)
						putwchar('\n');
					else
						wprintf(L"%.*ls\n", (int)length,
						    line);
					prev_header_type = hdr_ParagraphStart;
					continue;
				}
			} else {
				/*
				 * If this is an indented paragraph other
				 * than a mail header continuation, set
				 * |last_indent|.
				 */
				if (np != last_indent &&
				    header_type != hdr_Continuation)
					last_indent = np;
			}
			prev_header_type = header_type;
		}

		{
			size_t n = np;

			while (n < length) {
				/* Find word end and count spaces after it */
				size_t word_length = 0, space_length = 0;

				while (n + word_length < length &&
				    line[n + word_length] != ' ')
					++word_length;
				space_length = word_length;
				while (n + space_length < length &&
				    line[n + space_length] == ' ')
					++space_length;
				/* Send the word to the output machinery. */
				output_word(first_indent, last_indent,
				    line + n, word_length,
				    space_length - word_length);
				n += space_length;
			}
		}
		++para_line_number;
	}
	new_paragraph(output_in_paragraph ? last_indent : first_indent, 0);
	if (ferror(stream)) {
		warn("%s", name);
		++n_errors;
	}
}