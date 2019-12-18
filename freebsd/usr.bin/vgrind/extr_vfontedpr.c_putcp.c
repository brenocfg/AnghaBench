__attribute__((used)) static void
putcp(register int c)
{

	switch(c) {

	case 0:
		break;

	case '\f':
		break;

	case '\r':
		break;

	case '{':
		ps("\\*(+K{\\*(-K");
		break;

	case '}':
		ps("\\*(+K}\\*(-K");
		break;

	case '\\':
		ps("\\e");
		break;

	case '_':
		ps("\\*_");
		break;

	case '-':
		ps("\\*-");
		break;

	case '`':
		ps("\\`");
		break;

	case '\'':
		ps("\\'");
		break;

	case '.':
		ps("\\&.");
		break;

	case '*':
		ps("\\fI*\\fP");
		break;

	case '/':
		ps("\\fI\\h'\\w' 'u-\\w'/'u'/\\fP");
		break;

	default:
		if (c < 040)
			putchar('^'), c |= '@';
	case '\t':
	case '\n':
		putchar(c);
	}
}