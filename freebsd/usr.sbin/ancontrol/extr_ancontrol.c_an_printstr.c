__attribute__((used)) static void
an_printstr(char *str, int len)
{
	int			i;

	for (i = 0; i < len - 1; i++) {
		if (str[i] == '\0')
			str[i] = ' ';
	}

	printf("[ %.*s ]", len, str);
}