__attribute__((used)) static void show_line_to_eol(const char *line, int len, const char *reset)
{
	int saw_cr_at_eol = 0;
	if (len < 0)
		len = strlen(line);
	saw_cr_at_eol = (len && line[len-1] == '\r');

	printf("%.*s%s%s\n", len - saw_cr_at_eol, line,
	       reset,
	       saw_cr_at_eol ? "\r" : "");
}